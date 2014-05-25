#include <Splash.hpp>

Splash::Splash() {} // Constructeur vide

Splash::Splash ( int p , irr::scene::ISceneNode* sNode ) { // Constructeur à arguments
	
	pos = p; // On a la position
	sceneNode = sNode; // Et le noeud
}

irr::scene::ISceneNode* Splash::getSceneNode () { // Renvoie le noeud de scène

	return sceneNode;
}

int Splash::getPos () { // Renvoie la position

	return pos;
}

void Splash::setPos ( int p ) { // Change la position

	pos = p;
}

int Splash::getDirection () { // Renvoie la direction

	return dir;
}

void Splash::setDirection ( int d ) { // Change la direction

	dir = d;
}

void Splash::Animate ( irr::scene::ISceneManager* sceneManager ) { // Anime la boule en la faisant avancer

	int k = pos; // On récupère la position actuelle, avant qu'elle change
	switch ( dir ) { // Selon la direction, on va avancer dans un des 4 sens possibles
		case 0: // Vers le haut
			if ( pos/4 != 0 ) // On avance que si on est pas au bout du damier
				pos -= 4;
			break;
		case 1: // Droite
			if ( pos%4 != 0 )
				pos -= 1;
			break;
		case 2: // Bas
			if ( pos/4 != 3 )
				pos += 4;
			break;
		case 3: // Gauche
			if ( pos%4 != 3 )
				pos += 1;
			break;
	}
	if ( k != pos ) { // Si on a bougé

		sceneNode->addAnimator ( sceneManager->createFlyStraightAnimator ( irr::core::vector3df ( -45 + k%4 * 30 , 45 - k/4 * 30 , 5 ) , irr::core::vector3df ( -45 + pos%4 * 30 , 45 - pos/4 * 30 , 5 ) , 500 ) ); // On lance l'animation
		sceneNode->setVisible ( true ); // On rend la boule visible
	}
}

bool Splash::Stuck () { // Renvoie vrai si on peut plus avancer la boule

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
