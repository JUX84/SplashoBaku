#ifndef _SPLASH_HPP_
#define _SPLASH_HPP_

#include <irrlicht.h>

class Splash {

	private:
	int pos;
	irr::scene::ISceneNode* sceneNode;

	public:
	Splash();
	Splash ( int p , irr::scene::ISceneNode* sNode );
	irr::scene::ISceneNode* getSceneNode();
	int getPos();
	void setPos ( int p );
};

#endif
