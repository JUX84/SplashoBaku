#include <Splash.hpp>

class SplashDamier {

	private:
	int pos;
	int level;
	irr::scene::IAnimatedMeshSceneNode* sceneNode;

	public:
	SplashDamier();
	SplashDamier ( int p , int l , irr::scene::IAnimatedMeshSceneNode* sNode );
	irr::scene::IAnimatedMeshSceneNode* getSceneNode();
	int getLevel();
	void setLevel ( int l );
};
