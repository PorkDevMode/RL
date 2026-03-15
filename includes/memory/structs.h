#pragma once
#include <windows.h>
#include <cstdint>

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

	struct RTTICompleteObjectLocator {
		uint32_t signature;              // 0x00: Always 1 for x64
		uint32_t offset;                 // 0x04: Offset of this vtable in the complete class
		uint32_t cdOffset;               // 0x08: Constructor displacement offset
		uint32_t pTypeDescriptor;        // 0x0C: RVA of TypeDescriptor (relative to module base)
		uint32_t pClassDescriptor;       // 0x10: RVA of ClassHierarchyDescriptor (relative to module base)
		uint32_t pSelf;                  // 0x14: RVA of this structure itself (relative to module base)
	};

	struct PMD {
		int mdisp;                    // Member displacement
		int pdisp;                    // Vbtable displacement
		int vdisp;                    // Displacement inside vbtable
	};

	struct RTTITypeDescriptor {
		uintptr_t pVFTable;               // 0x00: Pointer to type_info vtable
		uintptr_t spare;                  // 0x08: Reserved/spare field
		char name[512];                   // 0x10: Mangled type name (null-terminated)
	};

	struct RTTIClassHierarchyDescriptor {
		uint32_t signature;              // 0x00: Always 0
		uint32_t attributes;             // 0x04: Bit flags
		uint32_t numBaseClasses;         // 0x08: Number of base classes
		uint32_t pBaseClassArray;        // 0x0C: RVA of base class array
	};

	struct RTTIBaseClassDescriptor {
		uint32_t pTypeDescriptor;        // 0x00: RVA of TypeDescriptor
		uint32_t numContainedBases;      // 0x04: Number of nested bases
		PMD where;                    // 0x08: Pointer-to-member displacement info
		uint32_t attributes;             // 0x14: Flags
		uint32_t pClassDescriptor;       // 0x18: RVA of ClassHierarchyDescriptor
	};
}
