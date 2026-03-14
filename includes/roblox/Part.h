#pragma once
#include "BasePart.h"

namespace RBX {
    class Part : public BasePart {
    public:
        Part() = default;
		explicit Part(uintptr_t instance_address) : BasePart(instance_address) {}
    private:
        bool valid_class() const;
    };
}