#include <SplashDamier.hpp>

SplashDamier::SplashDamier() {}

SplashDamier::SplashDamier ( int p , int l , irr::scene::IAnimatedMeshSceneNode* sNode ) {

	pos = p;
	level = l;
	sceneNode = sNode;
}

irr::scene::IAnimatedMeshSceneNode* SplashDamier::getSceneNode () {

	return sceneNode;
}

int SplashDamier::getLevel () {

	return level;
}

void SplashDamier::setLevel ( int l ) {

	level = l;
}
