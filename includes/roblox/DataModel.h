#pragma once

#include "Instance.h"
#include <thread>

namespace RBX {
	class DataModel : public Instance {
	public:
		DataModel(const DataModel&) = delete;
		DataModel& operator=(const DataModel&) = delete;
		static DataModel& get() {
			static DataModel instance;
			return instance;
		}

		void start();
		void stop();
		bool valid() const;
	private:
		DataModel() = default;
		std::thread m_update_thread;
		bool find_datamodel();
		void update_loop();
	};

	bool VerifyVersion();
}