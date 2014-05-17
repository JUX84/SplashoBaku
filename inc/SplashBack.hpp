#include <irrlicht.h>

#include <vector>
#include <list>

#include <Splash.hpp>
#include <SplashDamier.hpp>
#include <MouseEventReceiver.hpp>

class SplashBack {

	public:
		irr::IrrlichtDevice* device;
		irr::video::IVideoDriver* videoDriver;
		irr::scene::ISceneManager* sceneManager;
		irr::gui::IGUIEnvironment* guiEnv;
		irr::gui::IGUIFont* font;
		irr::scene::ICameraSceneNode* camera;
		irr::scene::ILightSceneNode* light;
		irr::scene::ISceneNode* currentNode;
		std::vector<irr::scene::ISceneNode*> damier;
		std::vector<SplashDamier> splashDamierVec;
		std::list<Splash> splashMagazine;
		std::list<Splash> splashActive;
		std::list<Splash> splashMini;
		MouseEventReceiver receiver;
		bool click;
		int combo;
		int level;

	public:
		SplashBack();
		void Render();
		bool Run();
		void Drop();
		void Init_Damier();
		void Init_SplashMagazine();
		void Init_SplashDamier();
		void Init_Game();
		void IncreaseSplash ( int i );
		void Tick();
		bool Empty();
};
