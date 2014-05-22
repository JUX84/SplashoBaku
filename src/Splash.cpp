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

int Splash::getDirection () {

	return dir;
}

void Splash::setDirection ( int d ) {

	dir = d;
}
#include <iostream>
void Splash::Animate ( irr::scene::ISceneManager* sceneManager ) {

	bool b = false;
	int k = pos;
	switch ( dir ) {
		case 0:
			if ( k/4 != 0 )
				k = pos - 4;
			break;
		case 1:
			if ( k%4 != 0 )
				k = pos - 1;
			break;
		case 2:
			if ( k/4 != 3 )
				k = pos + 4;
			break;
		case 3:
			if ( k%4 != 3 )
				k = pos + 1;
			break;
	}
	if ( k != pos ) {
		sceneNode->addAnimator ( sceneManager->createFlyStraightAnimator ( irr::core::vector3df ( -45 + pos%4 * 30 , 45 - pos/4 * 30 , 5 ) , irr::core::vector3df ( -45 + k%4 * 30 , 45 - k/4 * 30 , 5 ) , 1000 ) );
		sceneNode->setVisible ( true );
		pos = k;
	}
}

bool Splash::Stuck () {

	switch ( dir ) {
		case 0:
			if ( pos/4 == 0 )
				return true;
			break;
		case 1:
			if ( pos%4 == 0 )
				return true;
			break;
		case 2:
			if ( pos/4 == 3 )
				return true;
			break;
		case 3:
			if ( pos%4 == 3 )
				return true;
			break;
	}
	return false;
}
