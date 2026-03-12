#include "Instance.h"

namespace RBX {
    class Humanoid : public Instance {
	public : 
	    Humanoid() = default;
	    explicit Humanoid(uintptr_t instance_address) : Instance(instance_address){};
	    void set_walkspeed(float walkspeed) const;
	private :
	    bool class_valid() const;
    };
}
