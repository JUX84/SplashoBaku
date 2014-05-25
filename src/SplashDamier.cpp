#include <SplashDamier.hpp>

SplashDamier::SplashDamier() {} // Constructeur vide

SplashDamier::SplashDamier ( int p , int l , irr::scene::IAnimatedMeshSceneNode* sNode ) { // Constructeur à arguments

	pos = p; // Position
	level = l; // Taille
	sceneNode = sNode; // Noeud de scène
}

irr::scene::IAnimatedMeshSceneNode* SplashDamier::getSceneNode () { // Renvoie le noeud

	return sceneNode;
}

int SplashDamier::getLevel () { // Renvoie la taille

	return level;
}

void SplashDamier::setLevel ( int l ) { // Change la taille

	level = l;
}
