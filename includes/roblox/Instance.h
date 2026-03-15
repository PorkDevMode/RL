#pragma once

// TODO: use only needed includes in headers
#include "includes/memory/memory.h"
#include "Offsets.h"
#include "Structs.h"
#include <vector>

namespace RBX {
	class Instance {
	public:
		Instance() = default;
		explicit Instance(uintptr_t instance_address);
		virtual ~Instance() = default;
		explicit operator bool() const { return m_address > 0 && m_class_name.length() > 0; }

		uintptr_t address() const { return m_address; };
		std::string class_name() const;
		std::string name() const;
		Instance parent() const;
		std::vector<Instance> get_children() const;
		Instance find_first_child(const std::string& target_name) const;
		void debug_print() const { std::println("Address: {:#x}\nName: {}\nClass Name: {}", m_address, name(), class_name()); } // for testing

		template<typename T>
		T as() const { return T(m_address); }
	protected:
		uintptr_t m_address = 0;
		mutable std::string m_class_name = "";
	};
}