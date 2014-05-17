#include <Splash.hpp>

Splash::Splash() {}

Splash::Splash ( int p , irr::scene::ISceneNode* sNode ) {
	
	pos = p;
	sceneNode = sNode;
}

irr::scene::ISceneNode* Splash::getSceneNode () {

	return sceneNode;
}

int Splash::getPos () {

	return pos;
}

void Splash::setPos ( int p ) {

	pos = p;
}
