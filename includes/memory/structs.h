#pragma once
#include <windows.h>

// memory structs and definitions
#ifdef __cplusplus
extern "C" {
#endif
	typedef long NTSTATUS;
	typedef size_t SIZE_T;
	typedef SIZE_T* PSIZE_T;
#define NTAPI __stdcall
	NTSTATUS NTAPI NtReadVirtualMemory(
		HANDLE ProcessHandle,
		PVOID BaseAddress,
		PVOID Buffer,
		SIZE_T NumberOfBytesToRead,
		PSIZE_T NumberOfBytesRead
	);

	NTSTATUS NTAPI NtWriteVirtualMemory(
		HANDLE ProcessHandle,
		PVOID BaseAddress,
		PVOID Buffer,
		SIZE_T NumberOfBytesToWrite,
		PSIZE_T NumberOfBytesWritten
	);

	NTSTATUS NTAPI NtAllocateVirtualMemory(
		HANDLE ProcessHandle,
		PVOID* BaseAddress,
		ULONG_PTR ZeroBits,
		PSIZE_T RegionSize,
		ULONG AllocationType,
		ULONG PageProtection
	);

#ifdef __cplusplus
}
#endif

namespace MemoryStruct {
	struct ProcessInformation {
		HANDLE process_handle = 0;
		int pid = 0;
		uintptr_t base = 0;
		size_t base_size = 0;
	};
}
