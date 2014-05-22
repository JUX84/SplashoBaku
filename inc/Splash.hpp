#ifndef _SPLASH_HPP_
#define _SPLASH_HPP_

#include <irrlicht.h>

class Splash {

	private:
	int pos;
	int dir;
	irr::scene::ISceneNode* sceneNode;

	public:
	Splash();
	Splash ( int p , irr::scene::ISceneNode* sNode );
	irr::scene::ISceneNode* getSceneNode();
	int getPos();
	void setPos ( int p );
	int getDirection();
	void setDirection (int d );
	void Animate(irr::scene::ISceneManager* sceneManager);
	bool Stuck();
};

#endif
