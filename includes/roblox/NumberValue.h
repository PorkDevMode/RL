#pragma once

#include "Instance.h"

namespace RBX {
    class NumberValue : public Instance {
    public:
        NumberValue() = default;
        explicit NumberValue(uintptr_t instance_address) : Instance(instance_address) {}
        double get_value() const;
        void set_value(double value) const;
    private:
        bool valid_class() const;
    };
}