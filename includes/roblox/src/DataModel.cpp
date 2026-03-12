#include "../DataModel.h"
#include <regex>

/* TODO:
Way to kill the update thread,
Improve update loop to use less reads,
Generally improve DataModel class*/

void RBX::DataModel::start() {
	m_update_thread = std::thread(&DataModel::update_loop, this);
	m_update_thread.detach();
}

void RBX::DataModel::stop() {
	
}

bool RBX::DataModel::valid() const {
	if (!m_address) return false;
	if (m_class_name != "DataModel") return false;
	if (!mem.read<uintptr_t>(m_address + Offsets::DataModel::Workspace)) return false;
	return true;
}

bool RBX::DataModel::find_datamodel() {
	uintptr_t fake_datamodel = mem.read<uintptr_t>(mem.process_info.base + Offsets::FakeDataModel::Pointer);
	if (!fake_datamodel) return false;

	uintptr_t real_datamodel = mem.read<uintptr_t>(fake_datamodel + Offsets::FakeDataModel::RealDataModel);
	if (!real_datamodel || real_datamodel == m_address) return false;

	this->m_address = real_datamodel;
	this->m_class_name = this->class_name();

	if (m_class_name.empty() || m_class_name != "DataModel" || this->name() != "Ugc") {
		this->m_address = 0;
		return false;
	}

	return true;
}

void RBX::DataModel::update_loop() {
	while (true) {
		if (find_datamodel()) {
			std::println("Updated datamodel");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

bool RBX::VerifyVersion() {
	char buffer[MAX_PATH];
	DWORD size = MAX_PATH;

	if (!QueryFullProcessImageNameA(mem.process_info.process_handle, 0, buffer, &size))
		return false;

	std::string version(buffer, size);
	std::regex version_regex(R"(version-[a-f0-9]+)", std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_search(version, match, version_regex))
		return false;

	version = match.str();
	std::println("current version is: {}", version);

	if (version != Offsets::ClientVersion) {
		std::println("version mismatch, wanted version is: {}", Offsets::ClientVersion);
		return false;
	}

	return true;
}