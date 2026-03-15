#include "../NumberValue.h"

bool RBX::NumberValue::valid_class() const {
    if (!m_address || class_name() != "NumberValue")
        return false;
    return true;
}

double RBX::NumberValue::get_value() const {
    if (!valid_class())
        return 0.0;
    return mem.read<double>(m_address + Offsets::Misc::Value);
}

void RBX::NumberValue::set_value(double value) const {
    if (!valid_class())
        return;
    mem.write<double>(m_address + Offsets::Misc::Value, value);
}