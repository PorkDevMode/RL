#pragma once
#include <cstdint>

namespace RBX {
    template<typename T>
    T GetFastFlagValue(uintptr_t fflag_offset);
    template<typename T>
    void SetFastFlagValue(uintptr_t fflag_offset, T value);
}