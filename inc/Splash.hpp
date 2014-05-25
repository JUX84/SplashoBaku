#ifndef _SPLASH_HPP_
#define _SPLASH_HPP_

#include <irrlicht.h>

class Splash {

	private:
	int pos; // Position de la boule
	int dir; // Direction
	irr::scene::ISceneNode* sceneNode; // Noeud de scène

	public:
	Splash(); // Constructeur
	Splash ( int p , irr::scene::ISceneNode* sNode ); // Constructeur #2
	irr::scene::ISceneNode* getSceneNode(); // Renvoie le noeud de scène
	int getPos(); // Renvoie la position
	void setPos ( int p ); // Change la position
	int getDirection(); // Renvoie la direction
	void setDirection ( int d ); // Change la direction
	void Animate(irr::scene::ISceneManager* sceneManager); // Fais avancer la boule sur le damier
	bool Stuck(); // Renvoie vrai si la boule est arrivée au bout du damier
};

#endif
