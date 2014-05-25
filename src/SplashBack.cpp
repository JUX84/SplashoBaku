#include <SplashBack.hpp>
#include <iostream>
#include <random>

int random_number ( int start , int end ) { // Renvoie un nombre au hasard entre start et end

	std::random_device rd; // Création d'un objet random
	std::default_random_engine generator(rd()); // Création d'un générateur de nombre
	std::uniform_int_distribution<int> distribution(start,end); // Distribution d'un integer
	return distribution(generator);
}

SplashBack::SplashBack() { // Constructeur

	device = irr::createDevice ( irr::video::EDT_OPENGL , irr::core::dimension2d<irr::u32>( 640 , 480 ) , 16 , false , false , false , 0 ); // Création d'un objet Irrlicht ( driver vidéo , taille de la fenêtre , nombre de couleurs , ... )
	device->setEventReceiver ( &receiver ); // Assignation d'un récepteur
	videoDriver = device->getVideoDriver(); // Récupération d'un driver vidéo
	sceneManager = device->getSceneManager(); // Récupération du gestionaire de scène
	guiEnv = device->getGUIEnvironment(); // // environnement GUI
	font = guiEnv->getFont("resources/fonts/courier.bmp"); // Set la police
	camera = sceneManager->addCameraSceneNode ( 0 , irr::core::vector3df ( 0 , 0 , 100 ) , irr::core::vector3df ( 0 , 0 , 0 ) ); // Ajout de la caméra
	light = sceneManager->addLightSceneNode ( 0 , irr::core::vector3df ( 0 , 0 , 100 ) , irr::video::SColorf ( 1.0 , 1.0 , 1.0 ) , 1000.f , 1 ); // Ajout de la lumière
	click = false; // Initialisation de click
	level = 0; // Initialisation du niveau
}

void SplashBack::Init_Game () { // Initialisation du jeu

	for ( int i = 0 ; i < 16 ; ++i ) { // Pour toutes les cases

		for ( int j = 0 ; j < random_number(0,3) ; ++ j ) { // On va augmenter la taille de la boule 0 à 3 fois

			IncreaseSplash ( i ); // Augmentation de la taille de boule i
		}
	}
	level += 1; // On passe au niveau supérieur
}

void SplashBack::Init_Damier () { // Initialisation du damier

	irr::scene::IMesh* damierMesh = sceneManager->getMesh ( "resources/models/damier1.obj" ); // On récupère le modèle
	irr::video::ITexture* tex = videoDriver->getTexture ( "resources/textures/copper.jpg" ); // puis une texture
	irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( damierMesh ); // On crée un noeud de scène grâce au modèle précédent
	sceneNode->setMaterialTexture ( 0 , tex ); // On met la texture sur le modèle
	sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true ); // Activation des effets de lumière sur ce noeud de scène
	sceneNode->setID ( 0x1 ); // On lui attribue un ID qui sera utilisé pour la sélection via la souris
	sceneNode->setRotation ( irr::core::vector3df ( 90 , 0 , 0 ) ); // Rotation du damier

	for ( int i = 0 ; i < 16 ; ++i ) { // Pour chaque dalle du damier

		sceneNode->setPosition ( irr::core::vector3df ( -45 + i%4 * 30 , 45 - i/4 * 30 , 0 ) ); // On déplace le noeud
		sceneNode->setName ( irr::core::stringc ( i ) ); // On lui attribue un nom qui servira pour la sélection
		damier.push_back ( sceneNode->clone() ); // On l'insère dans le tableau du damier
	}

	sceneManager->addToDeletionQueue ( sceneNode ); // On supprime le noeud qui servait de modèle
}

void SplashBack::Init_SplashMagazine () { // Initialisation du chargeur de boules

	irr::scene::IMesh* splashMesh = sceneManager->getMesh ( "resources/models/splash3.obj" ); // Le modèle 3D
	irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( splashMesh ); // Création du noeud
	sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) ); // La texture
	sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true ); // Activation de la réaction à la lumière
	sceneNode->setID ( 0x0 ); // On donne l'ID 0 qui servira plus tard
	sceneNode->setScale ( irr::core::vector3df ( 0.2 , 0.2 , 0.2 ) ); // On rétrécie sa taille

	for ( int i = 0 ; i < 10 ; ++i ) { // On commence avec 10 boules

		sceneNode->setPosition ( irr::core::vector3df ( 0 , i*10 , 0 ) ); // On déplace le noeud
		splashMagazine.push_back ( Splash ( -(i+1) , sceneNode->clone() ) ); // On l'ajoute au tableau
	}

	sceneManager->addToDeletionQueue ( sceneNode ); // On supprime le noeud
}

void SplashBack::Init_SplashDamier () { // Initialisation des boules du jeu

	irr::scene::IAnimatedMesh* splashMesh = sceneManager->getMesh ( "resources/models/splashanimated2.md3" ); // On charge un modèle 3D animé
	irr::scene::IAnimatedMeshSceneNode* sceneNode = sceneManager->addAnimatedMeshSceneNode ( splashMesh ); // Création du noeud
	sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true ); // Réaction à la lumière active
	sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) ); // Ajout de la texture
	sceneNode->setID ( 0x0 ); // ID = 0
	sceneNode->setLoopMode ( false ); // Pas de loop pour l'animation
	sceneNode->setFrameLoop ( 0 , 0 ); // On bloque l'animation à la frame 0, c'est à dire que la boule fait une taille de 0, donc invisible

	for ( int i = 0 ; i < 16 ; ++i ) { // On a 16 boules

		sceneNode->setPosition ( irr::core::vector3df ( -45 + i%4 * 30 , 45 - i/4 * 30 , 5 ) ); // On déplace la boule
		splashDamierVec.push_back ( SplashDamier ( i , 0 , static_cast<irr::scene::IAnimatedMeshSceneNode*>(sceneNode->clone()) ) ); // On l'ajoute au tableau
	}

	sceneManager->addToDeletionQueue ( sceneNode ); // On supprime le noeud
}

void SplashBack::IncreaseSplash ( int i ) { // Augmentation de la taille de la boule i

	irr::scene::IAnimatedMeshSceneNode* sceneNode = splashDamierVec[i].getSceneNode(); // On récupère le noeud de la boule
	irr::s32 endFrame = sceneNode->getEndFrame(); // On récupère la frame de l'animation en cours
	sceneNode->setFrameLoop ( endFrame , endFrame + 15 ); // On y ajoute 15 frames pour l'animer
	splashDamierVec[i].setLevel ( splashDamierVec[i].getLevel() + 1 ); // On augmente sa taille
	if ( splashDamierVec[i].getLevel() == 4 ) { // Si la boule a atteint la taille maximale

		splashDamierVec[i].setLevel ( 0 ); // On la repasse à la taille 0
		irr::scene::IMesh *splashMesh = sceneManager->getMesh ( "resources/models/splash3.obj" ); // On récupère un modèle boule
		irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( splashMesh ); // On crée un noeud grâce à ce modèle
		sceneNode->setVisible ( false ); // On rend cette boule invisible
		sceneNode->setScale(irr::core::vector3df(0.2,0.2,0.2)); // On rétrécit sa taille
		sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) ); // On récupère une texture
		sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true ); // On active sa réaction à la lumière
		sceneNode->setID ( 0x0 ); // On lui attribue l'ID 0
		combo += 1; // On démarre un combo

		for ( int j = 0 ; j < 4 ; ++j ) { // On va créer 4 de ces boules

			Splash s ( i , sceneNode->clone() ); // Création d'un Splash
			s.setDirection ( j ); // On lui attribue une direction
			s.Animate(sceneManager); // On l'anime
			if ( i == s.getPos() ) // Si la boule ne s'est pas déplacée
				sceneManager->addToDeletionQueue ( s.getSceneNode() ); // On détruit la boule
			else
				splashActive.push_back ( s ); // Sinon on ajoute la boule dans le tableau des éléments actifs
		}
		sceneManager->addToDeletionQueue ( sceneNode ); // On supprime le noeud
	}
}

void SplashBack::Tick() { // Fonction lancée à chaque tick

	for ( int i = 0 ; i < 16 ; ++i ) { // On va vérifier l'état de l'animation de chaque boule

		irr::scene::IAnimatedMeshSceneNode* sceneNode = splashDamierVec[i].getSceneNode(); // On récupère le noeud de la boule i
		if ( sceneNode->getFrameNr() == 60 ) // Si une boule a atteint la fin de son animation
			sceneNode->setFrameLoop ( 0 , 0 ); // On remet cette dernière à 0
	}
	std::list<Splash>::iterator it = splashActive.begin(); // On crée un itérateur pour naviguer à travers les boules actives
	while ( it != splashActive.end() ) { // On va parcourer toutes les boules actives

		bool del = false; // Variable qui va permettre la suppression d'un élément sans créer de SEGFAULT
		irr::core::list<irr::scene::ISceneNodeAnimator*> AnimList = (*it).getSceneNode()->getAnimators(); // On récupère la liste d'animations liées à la boule
		irr::core::list<irr::scene::ISceneNodeAnimator*>::Iterator it2 = AnimList.begin(); // On place un itérateur au début de cette liste
		while ( it2 != AnimList.end() ) { // Tant qu'on a pas parcouru toutes les animations

			if ( (*it2)->hasFinished() ) { // Si l'animation est terminée

				(*it).getSceneNode()->removeAnimator(*it2); // On retire l'animation

				if ( (*it).getPos() >= 0 ) { // Si la boule est sur le damier

					if ( splashDamierVec[(*it).getPos()].getLevel() > 0 || combo == -1 ) { // S'il y a une boule à cet endroit, ou si on vient tout juste de cliquer
						sceneManager->addToDeletionQueue ( (*it).getSceneNode() ); // On supprime la boule active
						IncreaseSplash ( (*it).getPos() ); // On augmente la taille de la boule qui est là
						del = true; // On va supprimer l'élément courant
					}
					else if ( (*it).Stuck() ) { // Si la boule est arrivée au bout du damier
						sceneManager->addToDeletionQueue ( (*it).getSceneNode() ); // On la supprime
						del = true;
					}
					else { // Sinon

						(*it).Animate(sceneManager); // On continue l'animation de la boule et on avance
					}
				}
				else // Sinon
					del=true; // On supprime
			}
			++it2; // On avance l'itérateur pour passer à l'animation suivante
		}
		if ( del ) // Si l'on doit supprimer
			it = splashActive.erase ( it ); // On efface l'itérateur et récupére le suivant
		else // Sinon
			++it; // On continue d'avancer parmi les boules
	}
	if ( splashActive.size() == 0 ) { // Si toutes les animations sont terminées

		if ( combo > 0 ) { // Si des combos ont eu lieu pendant les dernières animations

			irr::scene::IMesh* splashMesh = sceneManager->getMesh ( "resources/models/splash3.obj" ); // On récupère un modèle 3D
			irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( splashMesh ); // On crée une boule
			sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) ); // On lui donne une texture
			sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true ); // On active la lumière
			sceneNode->setScale ( irr::core::vector3df ( 0.2 , 0.2 , 0.2 ) ); // On rétrécit la boule
			sceneNode->setID ( 0x0 ); // On lui donne l'ID 0

			for ( int i = 0 ; i < combo ; ++i ) { // Pour chaque combo

				sceneNode->setPosition ( irr::core::vector3df ( 0 , splashMagazine.size()*10 , 0 ) ); // On déplace la boule
				splashMagazine.push_back ( Splash ( -(splashMagazine.size()+1) , sceneNode->clone() ) ); // On l'ajoute au chargeur
			}

			sceneManager->addToDeletionQueue ( sceneNode ); // On détruit le noeud
		}
		combo = -1; // On réinitialise les combos
		if ( Empty() ) // Si le jeu est fini
			Init_Game(); // On le relance
		irr::core::line3df ray = sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates ( receiver.GetMouseState().Position , camera ); // On crée un rayon qui part de la caméra et se dirige vers les curseur de la souris
		currentNode = sceneManager->getSceneCollisionManager()->getSceneNodeFromRayBB ( ray , 0x1 ); // On récupère le premier noeud touché par le rayon. Ce noeud doit avoir l'ID 1 sinon il ne sera pas sélectionné (NB: Seuls les damiers ont l'ID 1)
		if ( currentNode != NULL ) { // Si un noeud est actuellement sélectionné

			if ( !receiver.GetMouseState().LeftButtonDown ) // Si on a relâché le clic gauche
				click = false; // On repasse le click à faux
			if ( receiver.GetMouseState().LeftButtonDown && !click && splashMagazine.size() != 0 ) { // Si on est en train de cliquer et qu'on ne le sait pas déjà, et qu'il reste des boules dans le chargeur

				click = true; // On dit qu'on sait qu'on a cliqué (pour éviter les répétitions à cause des ticks)
				int i = atoi ( currentNode->getName() ); // On récupère le nom du noeud sélectionné (un des damiers)
				Splash s = splashMagazine.front(); // On prend la première boule du chargeur
				splashMagazine.pop_front(); // On la pop
				irr::scene::ISceneNodeAnimator* anim = sceneManager->createFlyStraightAnimator ( irr::core::vector3df ( 0 , 0 , 0 ) , irr::core::vector3df ( -45 + i%4 * 30 , 45 - i/4 * 30 , 5 ) , 500 ); // On crée une animation qui va partir du centre de l'écran (là où il y a la première boule du chargeur) qui va aller vers là où on a cliqué
				s.getSceneNode()->addAnimator ( anim ); // On attribue cette animation à la boule du chargeur
				s.setPos ( i ); // On change sa position
				splashActive.push_back ( s ); // On l'ajoute aux boules actives
				for ( std::list<Splash>::iterator it = splashMagazine.begin() ; it != splashMagazine.end() ; it++ ) { // Pour chaque boule du chargeur

					irr::scene::ISceneNodeAnimator* anim = sceneManager->createFlyStraightAnimator ( irr::core::vector3df ( 0 , - ( (*it).getPos() + 1 ) * 10 , 0 ) , irr::core::vector3df ( 0 , - ( (*it).getPos() + 2 ) * 10 , 0 ) , 500 ); // On crée l'animation qui va les replacer
					(*it).getSceneNode()->addAnimator ( anim ); // On leur ajoute l'animation
					(*it).setPos ( (*it).getPos() + 1 ); // On change leur position
					Splash active ( *it ); // On crée un pointeur sur la boule
					splashActive.push_back ( active ); // On l'ajoute aux boules actives
				}
			}
		}
	}
}

bool SplashBack::Empty () { // Renvoie vrai s'il n'y a plus de boules sur les dalles du damier

	for ( int i = 0 ; i < 16 ; ++i ) { // On vérifie chaque dalle

		if ( splashDamierVec[i].getLevel() != 0 ) // Si une boule a une taille diffèrente de 0
			return false; // Renvoie faux
	}
	return true; // Vrai sinon
}

void SplashBack::Render() { // Rendement de la scène

	videoDriver->beginScene ( true , true , irr::video::SColor ( 0 , 0 , 0 , 0 ) ); // On démarre la scène
	sceneManager->drawAll(); // On dessine tous les noeuds
	guiEnv->drawAll(); // On dessine le GUI
	irr::core::stringw text = L"Level "; // On ajoute le texte qui va informer du niveau
	text += irr::core::stringw(level); // que l'on a dans la variable level
	font->draw(text,irr::core::rect<irr::s32>(130,10,300,50),irr::video::SColor(255,255,255,255)); // On dessine le texte
	videoDriver->endScene(); // On finit la scène
}

bool SplashBack::Run() { // Renvoie vrai si la fenêtre est active, faux sinon

	return device->run();
}

void SplashBack::Drop() { // Détruit Irrlicht

	device->drop();
}
