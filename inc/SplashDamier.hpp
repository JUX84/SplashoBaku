#include <Splash.hpp>

class SplashDamier {

	private:
	int pos; // Position de la boule
	int level; // Taille de la boule
	irr::scene::IAnimatedMeshSceneNode* sceneNode; // Noeud de scène de la boule (modèle, texture et autres)

	public:
	SplashDamier(); // Constructeur
	SplashDamier ( int p , int l , irr::scene::IAnimatedMeshSceneNode* sNode ); // Constructeur ( p = position , l = taille , sNode = noeud de scène )
	irr::scene::IAnimatedMeshSceneNode* getSceneNode(); // Renvoie le noeud de scène
	int getLevel(); // Renvoie la taille
	void setLevel ( int l ); // Change la taille
};
