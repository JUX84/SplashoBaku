#include <irrlicht.h>

#include <vector>
#include <list>

#include <Splash.hpp>
#include <SplashDamier.hpp>
#include <MouseEventReceiver.hpp>

class SplashBack {

	public:
		irr::IrrlichtDevice* device; // Objet Irrlicht
		irr::video::IVideoDriver* videoDriver; // Driver vidéo
		irr::scene::ISceneManager* sceneManager; // Gestionnaire de la scène
		irr::gui::IGUIEnvironment* guiEnv; // Environnement GUI
		irr::gui::IGUIFont* font; // Police de caractères
		irr::scene::ICameraSceneNode* camera; // Caméra
		irr::scene::ILightSceneNode* light; // Lumière
		irr::scene::ISceneNode* currentNode; // Noeud de scène actuel
		std::vector<irr::scene::ISceneNode*> damier;
		std::vector<SplashDamier> splashDamierVec; // Tableau stockant les modèles 3D du damier
		std::list<Splash> splashMagazine; // Tableau stockant les recharges de boules
		std::list<Splash> splashActive; // Tableau stockant les boules actives (déplacement, transformation)
		std::list<Splash> splashMini; // Tableau stockant les mini-boules créées par des explosions
		MouseEventReceiver receiver; // Recepteur de signaux de la souris
		bool click; // Booléen nécessaire pour le bon fonctionnement du clic gauche
		int combo; // Variable permettant de gérer les combos
		int level; // Variable permettant de stocker le niveau actuel

	public:
		SplashBack(); // Constructeur
		void Render(); // Rendement des modèles 3D et des textures
		bool Run(); // Renvoir vrai si la fenêtre est encore ouverte, faux sinon
		void Drop(); // Arrêt du fonctionnement d'Irrlicht
		void Init_Damier(); // Initialisation du damier
		void Init_SplashMagazine(); // Initialisation des recharges
		void Init_SplashDamier(); // Initialisation des boules de départ
		void Init_Game(); // Initialisation du jeu
		void IncreaseSplash ( int i ); // Augmentation de la boule i ( x = i/4 , y = i%4 )
		void Tick(); // Fonction activée à chaque tick du programme
		bool Empty(); // Renvoie vrai s'il n'y a plus aucune boule sur le damier, faux sinon
};
