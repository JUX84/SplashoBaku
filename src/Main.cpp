#include <SplashBack.hpp>

int main () {

	SplashBack SB;
	SB.Init_Damier();
	SB.Init_SplashMagazine();
	SB.Init_SplashDamier();
	while ( SB.Run() ) {
		SB.Tick();
		SB.Render();
	}
	SB.Drop();
	return 0;
}
