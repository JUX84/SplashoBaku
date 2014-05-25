#include <irrlicht.h>

struct SMouseState { // Structure stockant l'état de la souris

	irr::core::position2di Position; // Position du curseur
	bool LeftButtonDown; // Booleen pour le clic gauche
	SMouseState() : LeftButtonDown(false) {} // Constructeur
};

class MouseEventReceiver : public irr::IEventReceiver { // Classe qui reçoit les infos de la souris

	public:
		SMouseState MouseState; // Etat de la souris

		virtual bool OnEvent ( const irr::SEvent& event ); // Appel en cas de mouvement ou de clic
		const SMouseState& GetMouseState() const; // Récupération de l'état de la souris
		MouseEventReceiver(); // Constructeur
};
