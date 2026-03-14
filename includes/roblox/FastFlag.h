#pragma once
#include <cstdint>
#include "includes/memory/memory.h"

namespace RBX {
    template<typename T>
    T GetFastFlagValue(uintptr_t fflag_offset) {
        if (!mem.initialized) return {};
        return mem.read<T>(mem.process_info.base + fflag_offset);
    }

    template<typename T>
    void SetFastFlagValue(uintptr_t fflag_offset, T value) {
        if (!mem.initialized) return;
        mem.write<T>(mem.process_info.base + fflag_offset, value);
    }
}