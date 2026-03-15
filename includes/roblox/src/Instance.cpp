#include "../Instance.h"

RBX::Instance::Instance(uintptr_t instance_address) {
	uintptr_t class_descriptor = mem.read<uintptr_t>(instance_address + Offsets::Instance::ClassDescriptor);
	if (!class_descriptor) return;

	uintptr_t class_name_ptr = mem.read<uintptr_t>(class_descriptor + Offsets::Instance::ClassName);
	if (!class_name_ptr) return;

	std::string class_name = mem.read_rstr(class_name_ptr);
	if (class_name.length() == 0) return;

	m_class_name = class_name;
	m_address = instance_address;
}

std::string RBX::Instance::name() const {
	if (!m_address) return "";

	uintptr_t name_ptr = mem.read<uintptr_t>(m_address + Offsets::Instance::Name);
	if (!name_ptr)
		return "";

	return mem.read_rstr(name_ptr);
}

std::string RBX::Instance::class_name() const {
	if (!m_address) return "";

	if (m_class_name.empty()) {
		uintptr_t class_descriptor = mem.read<uintptr_t>(m_address + Offsets::Instance::ClassDescriptor);
		if (!class_descriptor) return "";

		uintptr_t class_name_ptr = mem.read<uintptr_t>(class_descriptor + Offsets::Instance::ClassName);
		if (!class_name_ptr) return "";

		std::string class_name = mem.read_rstr(class_name_ptr);
		if (class_name.length() == 0) return "";

		m_class_name = class_name;
		return class_name;
	}
	else {
		return m_class_name;
	}
}

RBX::Instance RBX::Instance::parent() const {
	if (!m_address) return {};

	uintptr_t parent_ptr = mem.read<uintptr_t>(m_address + Offsets::Instance::Parent);
	if (!parent_ptr) return {};

	return RBX::Instance(parent_ptr);
}

std::vector<RBX::Instance> RBX::Instance::get_children() const {
	if (!m_address) return {};

	uintptr_t children_ptr = mem.read<uintptr_t>(m_address + Offsets::Instance::ChildrenStart);
	if (!children_ptr) return {};

	uintptr_t children_start = mem.read<uintptr_t>(children_ptr);
	uintptr_t children_end = mem.read<uintptr_t>(children_ptr + Offsets::Instance::ChildrenEnd);
	if (!children_start || !children_end) return {};

	size_t children_amount = (children_end - children_start) / 0x10;

	std::vector<RBX::Instance> buffer;
	buffer.reserve(children_amount);

	while (children_start != children_end) {
		uintptr_t child_address = mem.read<uintptr_t>(children_start);
		if (!child_address) break;

		RBX::Instance child(child_address);
		if (child && buffer.size() < children_amount)
			buffer.push_back(child);
		children_start += 0x10;
	}

	return buffer;
}

RBX::Instance RBX::Instance::find_first_child(const std::string& target_name) const { // repeat code ik but will save on memory this way
	if (!m_address) return {};

	uintptr_t children_ptr = mem.read<uintptr_t>(m_address + Offsets::Instance::ChildrenStart);
	if (!children_ptr) return {};

	uintptr_t children_start = mem.read<uintptr_t>(children_ptr);
	uintptr_t children_end = mem.read<uintptr_t>(children_ptr + Offsets::Instance::ChildrenEnd);
	if (!children_start || !children_end) return {};

	while (children_start != children_end) {
		uintptr_t child_address = mem.read<uintptr_t>(children_start);
		if (child_address) {
			uintptr_t name_ptr = mem.read<uintptr_t>(child_address + Offsets::Instance::Name); // read name before initializing to be more efficient
			if (!name_ptr)
				continue;

			if (mem.read_rstr(name_ptr) == target_name) {
				Instance child(child_address);
				return child;
			}
		}
		children_start += 0x10;
	}
	return {};
}