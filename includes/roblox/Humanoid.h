#include "Instance.h"
#include "Structs.h"

namespace RBX {
    class Humanoid : public Instance {
	public: 
	    Humanoid() = default;
	    explicit Humanoid(uintptr_t instance_address) : Instance(instance_address){}

		bool get_autojump() const;
		void set_autojump(bool value) const;

		bool get_use_jump_power() const;
		void set_use_jump_power(bool value) const;

		bool get_evaluate_state_machine() const;
		void set_evaulate_state_machine(bool value) const;

		bool get_sit() const;
		void set_sit(bool value) const;

		bool get_platform_stand() const;
		void set_platform_stand(bool value) const;

		bool get_walking() const;
		void set_walking(bool value) const;

		bool get_requires_neck() const;
		void set_requires_neck(bool value) const;

		std::string get_display_name() const;
		void set_display_name(std::string name) const;

		HumanoidStateType get_humanoid_state() const;
		void set_humanoid_state(HumanoidStateType type) const;

		NameOcclusion get_name_occlusion() const;
		void set_name_occlusion(NameOcclusion occlusion) const;

		HumanoidRigType get_rig_type() const;
		void set_rig_type(HumanoidRigType type) const;

		HealthDisplayType get_health_display_type() const;
		void set_health_display_type(HealthDisplayType type) const;

		Instance get_seat_part() const;
		void set_seat_part(const Instance& instance) const;

		Vector3 get_camera_offset() const;
		void set_camera_offset(Vector3 offset) const;

		/*
		Read and write as int32_t, or it will fucking die.
		Not sure about writing to it since its readonly
		*/
		Material get_floor_material() const;
		void set_floor_material(Material material) const; 

		float get_walkspeed() const;
	    void set_walkspeed(float walkspeed) const;
		void set_walkspeed(int walkspeed) const;
		
		float get_hipheight() const;
		void set_hipheight(float value) const;

		float get_health() const;
		void set_health(float value) const;

		float get_max_health() const;
		void set_max_health(float value) const;

		float get_max_slope_angle() const;
		void set_max_slope_angle(float value) const;

		float get_jump_height() const; // make sure to check jump power enabled first
		void set_jump_height(float value) const;

		float get_jump_power() const; // make sure jump power is enabled
		void set_jump_power(float value) const;

		float get_health_display_distance() const;
		void set_health_display_distance(float value) const;
	private:
	    bool class_valid() const;
    };
}
