#include "Instance.h"

namespace RBX {
    class Humanoid : public Instance {
	public: 
	    Humanoid() = default;
	    explicit Humanoid(uintptr_t instance_address) : Instance(instance_address){};
	    void set_walkspeed(int walkspeed) const;
	private:
>>>>>>> 895b24ef88816d4bc9043b3873c0441dbd2d2e8e
	    bool class_valid() const;
    };
}
