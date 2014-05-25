#include <MouseEventReceiver.hpp>

bool MouseEventReceiver::OnEvent ( const irr::SEvent& event ) {

	if ( event.EventType == irr::EET_MOUSE_INPUT_EVENT ) { // Si une action a été faite par la souris (mouvement ou clic)

		switch ( event.MouseInput.Event ) {

			case irr::EMIE_LMOUSE_PRESSED_DOWN: // Appui sur le clic gauche
				MouseState.LeftButtonDown = true;
				break;
			case irr::EMIE_LMOUSE_LEFT_UP: // Relâchement du clic gauche
				MouseState.LeftButtonDown = false;
				break;
			case irr::EMIE_MOUSE_MOVED: // Mouvement de la souris -> Récupération des coordonnées
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;
			default:
				break;
		}
	}
}

const SMouseState& MouseEventReceiver::GetMouseState() const { // Renvoie l'état de la souris

	return MouseState;
}

MouseEventReceiver::MouseEventReceiver() {} // Constructeur
