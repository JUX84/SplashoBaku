#include <SplashBack.hpp>

int main () {

	SplashBack SB; // Création de l'objet SplashBack
	SB.Init_Damier(); // Initialisation du damier
	SB.Init_SplashMagazine(); // Initialisation du chargeur de boules
	SB.Init_SplashDamier(); // Initialisation des boules
	while ( SB.Run() ) { // Tant que la fenêtre est active
		SB.Tick(); // Tick
		SB.Render(); // Rendement des modèles et textures
	}
	SB.Drop(); // Arrêt
	return 0;
}
