#pragma once

#include "structs.h"
#include <cstdint>
#include <minwindef.h>
#include <tlhelp32.h>
#include <print>
#include <vector>
#include <cstddef>
#include <winternl.h>

/*
only chatgpt, god and i know what the fuck i was thinking making this, dont even bother trying to refactor burn it and build it back up.
*/

namespace Memory {
	class Mem {
	public:
		bool initialized = false;
		MemoryStruct::ProcessInformation process_info = {};

		~Mem() {
			if (process_info.process_handle) {
				CloseHandle(process_info.process_handle);
			}
		}

		bool initialize(const char* process_name) {
			process_info.pid = get_pid(process_name);
			if (!process_info.pid) {
				return false;
			}

			process_info.process_handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, process_info.pid);
			if (process_info.process_handle == INVALID_HANDLE_VALUE || process_info.process_handle == nullptr) {
				return false;
			}

			std::vector<uintptr_t> base_information = get_base(process_info.pid, process_name);
			process_info.base = base_information[0];
			process_info.base_size = base_information[1];
			if (process_info.base == 0 || process_info.base_size == 0) {
				return false;
			}

			this->initialized = true;
			return true;
		}

		template<typename T>
		T read(uintptr_t address) {
			T buffer{};
			SIZE_T bytes_read = 0;
			NTSTATUS status = NtReadVirtualMemory(
				process_info.process_handle,
				(void*)address,
				&buffer,
				sizeof(T),
				&bytes_read
			);
			if (!NT_SUCCESS(status) || bytes_read != sizeof(T)) {
				return T{};
			}
			return buffer;
		}

		uintptr_t pattern_scan(const std::string& pattern) {
			MEMORY_BASIC_INFORMATION mbi;
			uintptr_t address = 0;
			uintptr_t max_address = 0x7FFFFFFF0000;

			while (address < max_address) {
				if (VirtualQueryEx(process_info.process_handle, reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi)) == 0)
					break;

				if (mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_GUARD) == 0 &&
					(mbi.Protect & PAGE_NOACCESS) == 0 && mbi.Type == MEM_PRIVATE) {

					std::vector<char> buffer(mbi.RegionSize);
					SIZE_T bytes_read = 0;

					NTSTATUS status = NtReadVirtualMemory(
						process_info.process_handle,
						mbi.BaseAddress,
						buffer.data(),
						mbi.RegionSize,
						&bytes_read
					);

					if (NT_SUCCESS(status) && bytes_read > pattern.length()) {
						for (size_t i = 0; i < bytes_read - pattern.length(); i++) {
							if (memcmp(&buffer[i], pattern.c_str(), pattern.length()) == 0) {
								return reinterpret_cast<uintptr_t>(mbi.BaseAddress) + i;
							}
						}
					}
				}

				address = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
			}

			return 0;
		}

		void read_buffer(uintptr_t address, void* buffer, size_t size) {
			SIZE_T bytes_read = 0;
			NTSTATUS status = NtReadVirtualMemory(
				process_info.process_handle,
				(void*)address,
				buffer,
				size,
				&bytes_read
			);
			if (!NT_SUCCESS(status) || bytes_read != size) {
				memset(buffer, 0, size);
			}
		}

		template<typename T>
		void write(uintptr_t address, T buffer) {
			SIZE_T bytes_written = 0;
			NtWriteVirtualMemory(
				process_info.process_handle,
				(void*)address,
				&buffer,
				sizeof(T),
				&bytes_written
			);
		}

		template<typename T>
		void write(uintptr_t address, T buffer, size_t buffer_size) {
			SIZE_T bytes_written = 0;
			NtWriteVirtualMemory(
				process_info.process_handle,
				(void*)address,
				&buffer,
				buffer_size,
				&bytes_written
			);
		}

		void write_weird_string(uintptr_t address, const std::string& str, uintptr_t size_ptr = 0) {
			if (!process_info.process_handle) return;

			size_ptr = size_ptr ? size_ptr : address + 0x10;
			size_t str_length = str.size();

			uint64_t current_size = read<uint64_t>(size_ptr);
			uintptr_t write_address = (current_size >= 16) ? read<uintptr_t>(address) : address;

			SIZE_T bytes_written = 0;
			NtWriteVirtualMemory(
				process_info.process_handle,
				(void*)write_address,
				(PVOID)str.data(),
				str.size(),
				&bytes_written
			);

			NtWriteVirtualMemory(
				process_info.process_handle,
				(void*)size_ptr,
				&str_length,
				sizeof(str_length),
				&bytes_written
			);
		}

		std::string read_weird_string(uintptr_t address, uintptr_t size_ptr = 0) {
			if (!process_info.process_handle) return "";

			size_ptr = size_ptr ? size_ptr : address + 0x10;

			uint64_t str_length = read<uint64_t>(size_ptr);

			if (str_length == 0) return "";

			uintptr_t read_address = (str_length >= 16) ? read<uintptr_t>(address) : address;

			if (!read_address) return "";

			std::vector<char> buffer(str_length + 1);
			SIZE_T bytes_read = 0;

			NTSTATUS status = NtReadVirtualMemory(
				process_info.process_handle,
				(void*)read_address,
				buffer.data(),
				str_length,
				&bytes_read
			);

			if (status != 0 || bytes_read != str_length) return "";

			buffer[str_length] = '\0';
			return std::string(buffer.data(), str_length);
		}

		std::string read_str(uintptr_t address, size_t max_len = 256) {
			if (!process_info.process_handle) return {};

			std::string result;
			result.resize(max_len);

			SIZE_T bytes_read = 0;
			NTSTATUS status = NtReadVirtualMemory(
				process_info.process_handle,
				(void*)address,
				result.data(),
				max_len,
				&bytes_read
			);
			if (status != 0 || bytes_read == 0) return {};

			size_t len = result.find('\0');
			if (len != std::string::npos)
				result.resize(len);
			else
				result.resize(bytes_read);

			return result;
		}

		void write_str(uintptr_t address, const std::string& str) {
			if (!process_info.process_handle) return;

			SIZE_T bytes_written = 0;
			NtWriteVirtualMemory(
				process_info.process_handle,
				(void*)address,
				(PVOID)str.data(),
				str.size(),
				&bytes_written
			);

			char null_term = '\0';
			NtWriteVirtualMemory(
				process_info.process_handle,
				(void*)(address + str.size()),
				&null_term,
				1,
				&bytes_written
			);
		}

		std::wstring read_wstr(uintptr_t address, size_t max_len = 256) {
			if (!process_info.process_handle) return {};

			std::wstring result;
			result.resize(max_len);

			SIZE_T bytes_read = 0;
			NTSTATUS status = NtReadVirtualMemory(
				process_info.process_handle,
				(void*)address,
				result.data(),
				max_len * sizeof(wchar_t),
				&bytes_read
			);
			if (status != 0 || bytes_read == 0) return {};

			size_t wchar_count = bytes_read / sizeof(wchar_t);
			size_t len = result.find(L'\0');
			if (len != std::wstring::npos)
				result.resize(len);
			else
				result.resize(wchar_count);

			return result;
		}

		std::string read_rstr(uintptr_t address, size_t max_len = 256) {
			if (!process_info.process_handle) return {};

			int str_length = read<int>(address + 0x10);
			if (str_length >= 16) {
				uintptr_t str_ptr = read<uintptr_t>(address);
				return read_str(str_ptr, max_len);
			}
			else {
				return read_str(address, max_len);
			}
		}

		void write_rstr(uintptr_t address, const std::string& str) {
			if (!process_info.process_handle) return;

			int old_length = read<int>(address + 0x10);
			int new_length = str.length();

			if (old_length >= 16) {
				uintptr_t str_ptr = read<uintptr_t>(address);
				if (!str_ptr) return;

				if (new_length >= 16) {
					write_str(str_ptr, str);
					write<int>(address + 0x10, new_length);
				}
				else {
					write_str(address, str);
					write<int>(address + 0x10, new_length);
				}
			}
			else {
				if (new_length >= 16) {
					return;
				}
				else {
					write_str(address, str);
					write<int>(address + 0x10, new_length);
				}
			}
		}

		std::string read_rtti(uintptr_t vtable) {
			if (!process_info.process_handle) 
				return "";

			uintptr_t col_ptr = read<uintptr_t>(vtable - sizeof(uintptr_t));
			if (!col_ptr)
				return "";

			MemoryStruct::RTTICompleteObjectLocator col = read<MemoryStruct::RTTICompleteObjectLocator>(col_ptr);
			MemoryStruct::RTTITypeDescriptor type_descriptor = read<MemoryStruct::RTTITypeDescriptor>(process_info.base + col.pTypeDescriptor);

			return type_descriptor.name;
		}
	private:
		int get_pid(const char* process_name) {
			int len = MultiByteToWideChar(CP_ACP, 0, process_name, -1, nullptr, 0);
			if (len == 0) return 0;
			wchar_t* w_process_name = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, process_name, -1, w_process_name, len);

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (snapshot == INVALID_HANDLE_VALUE) {
				std::println("[MEMORY] Failed to open tool32snapshot");
				return 0;
			}

			PROCESSENTRY32W process_entry;
			process_entry.dwSize = sizeof(PROCESSENTRY32W);

			if (!Process32FirstW(snapshot, &process_entry)) {
				delete[] w_process_name;
				CloseHandle(snapshot);
				return 0;
			}

			while (Process32NextW(snapshot, &process_entry)) {
				if (_wcsicmp(process_entry.szExeFile, w_process_name) == 0) {
					CloseHandle(snapshot);
					delete[] w_process_name;
					return process_entry.th32ProcessID;
				}
			}

			delete[] w_process_name;
			CloseHandle(snapshot);
			return 0;
		}

		std::vector<uintptr_t> get_base(int pid, const char* module_name) {
			std::vector<uintptr_t> base_info = { 0, 0 };

			int len = MultiByteToWideChar(CP_ACP, 0, module_name, -1, nullptr, 0);
			if (len == 0)
				return base_info;
			wchar_t* w_module_name = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, module_name, -1, w_module_name, len);

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
			if (snapshot == INVALID_HANDLE_VALUE) {
				delete[] w_module_name;
				return base_info;
			}

			MODULEENTRY32W module_entry;
			module_entry.dwSize = sizeof(MODULEENTRY32W);

			if (Module32FirstW(snapshot, &module_entry)) {
				do {
					if (_wcsicmp(module_entry.szModule, w_module_name) == 0) {
						base_info[0] = (uintptr_t)module_entry.modBaseAddr;
						base_info[1] = (uintptr_t)module_entry.modBaseSize;
						break;
					}
				} while (Module32NextW(snapshot, &module_entry));
			}

			delete[] w_module_name;
			CloseHandle(snapshot);
			return base_info;
		}
	};
}

inline Memory::Mem mem;
