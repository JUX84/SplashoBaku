#include <irrlicht.h>

using namespace irr;

struct SMouseState {

	core::position2di Position;
	bool LeftButtonDown;
	SMouseState() : LeftButtonDown(false) {}
};

class MouseEventReceiver : public IEventReceiver {

	public:
		SMouseState MouseState;

		virtual bool OnEvent ( const SEvent& event );
		const SMouseState& GetMouseState() const;
		MouseEventReceiver();
};
