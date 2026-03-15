#include "../Part.h"

bool RBX::Part::valid_class() const {
    return (m_address > 0 && class_name() == "Part");
}