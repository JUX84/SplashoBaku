#include <SplashBack.hpp>
#include <iostream>
#include <random>

int random_number ( int start , int end ) {

	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(start,end);
	return distribution(generator);
}

SplashBack::SplashBack() {

	device = irr::createDevice ( irr::video::EDT_OPENGL , irr::core::dimension2d<u32>( 640 , 480 ) , 16 , false , false , false , 0 );
	device->setEventReceiver ( &receiver );
	videoDriver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	guiEnv = device->getGUIEnvironment();
	font = guiEnv->getFont("resources/fonts/courier.bmp");
	camera = sceneManager->addCameraSceneNode ( 0 , irr::core::vector3df ( 0 , 0 , 100 ) , irr::core::vector3df ( 0 , 0 , 0 ) );
	light = sceneManager->addLightSceneNode ( 0 , irr::core::vector3df ( 0 , 0 , 100 ) , irr::video::SColorf ( 1.0 , 1.0 , 1.0 ) , 1000.f , 1 );
	click = false;
	level = 0;
}

void SplashBack::Init_Game () {

	for ( int i = 0 ; i < 16 ; ++i ) {

		for ( int j = 0 ; j < random_number(0,3) ; ++ j ) {

			IncreaseSplash ( i );
		}
	}
	level += 1;
}

void SplashBack::Init_Damier () {

	irr::scene::IMesh* damierMesh = sceneManager->getMesh ( "resources/models/damier1.obj" );
	irr::video::ITexture* tex = videoDriver->getTexture ( "resources/textures/copper.jpg" );
	irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( damierMesh );
	sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true );
	sceneNode->setID ( 0x1 );
	sceneNode->setRotation ( irr::core::vector3df ( 90 , 0 , 0 ) );

	for ( int i = 0 ; i < 16 ; ++i ) {

		sceneNode->setMaterialTexture ( 0 , tex );
		sceneNode->setPosition ( irr::core::vector3df ( -45 + i%4 * 30 , 45 - i/4 * 30 , 0 ) );
		sceneNode->setName ( irr::core::stringc ( i ) );
		damier.push_back ( sceneNode->clone() );
	}

	sceneManager->addToDeletionQueue ( sceneNode );
}

void SplashBack::Init_SplashMagazine () {

	irr::scene::IMesh* splashMesh = sceneManager->getMesh ( "resources/models/splash3.obj" );
	irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( splashMesh );
	sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) );
	sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true );
	sceneNode->setID ( 0x0 );
	sceneNode->setScale ( irr::core::vector3df ( 0.2 , 0.2 , 0.2 ) );

	for ( int i = 0 ; i < 100 ; ++i ) {

		sceneNode->setPosition ( irr::core::vector3df ( 0 , i*10 , 0 ) );
		splashMagazine.push_back ( Splash ( -(i+1) , sceneNode->clone() ) );
	}

	sceneManager->addToDeletionQueue ( sceneNode );
}

void SplashBack::Init_SplashDamier () {

	irr::scene::IAnimatedMesh* splashMesh = sceneManager->getMesh ( "resources/models/splashanimated2.md3" );
	irr::scene::IAnimatedMeshSceneNode* sceneNode = sceneManager->addAnimatedMeshSceneNode ( splashMesh );
	sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true );
	sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) );
	sceneNode->setID ( 0x0 );
	sceneNode->setLoopMode ( false );
	sceneNode->setFrameLoop ( 0 , 0 );

	for ( int i = 0 ; i < 16 ; ++i ) {

		sceneNode->setPosition ( irr::core::vector3df ( -45 + i%4 * 30 , 45 - i/4 * 30 , 5 ) );
		splashDamierVec.push_back ( SplashDamier ( i , 0 , static_cast<irr::scene::IAnimatedMeshSceneNode*>(sceneNode->clone()) ) );
	}

	sceneManager->addToDeletionQueue ( sceneNode );
}

void SplashBack::IncreaseSplash ( int i ) {

	irr::scene::IAnimatedMeshSceneNode* sceneNode = splashDamierVec[i].getSceneNode();
	irr::s32 endFrame = sceneNode->getEndFrame();
	sceneNode->setFrameLoop ( endFrame , endFrame + 15 );
	splashDamierVec[i].setLevel ( splashDamierVec[i].getLevel() + 1 );
	if ( splashDamierVec[i].getLevel() == 4 ) {

		splashDamierVec[i].setLevel ( 0 );
		irr::scene::IMesh *splashMesh = sceneManager->getMesh ( "resources/models/splash3.obj" );
		irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( splashMesh );
		sceneNode->setVisible ( false );
		sceneNode->setScale(irr::core::vector3df(0.2,0.2,0.2));
		sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) );
		sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true );
		sceneNode->setID ( 0x0 );
		combo += 1;

		for ( int j = 0 ; j < 4 ; ++j ) {

			Splash s ( i , sceneNode->clone() );
			s.setDirection ( j );
			s.Animate(sceneManager);
			if ( i == s.getPos() )
				sceneManager->addToDeletionQueue ( s.getSceneNode() );
			else
				splashActive.push_back ( s );

			sceneManager->addToDeletionQueue ( sceneNode );
		}
	}
}

void SplashBack::Tick() {

	for ( int i = 0 ; i < 16 ; ++i ) {

		irr::scene::IAnimatedMeshSceneNode* sceneNode = splashDamierVec[i].getSceneNode();
		if ( sceneNode->getFrameNr() == 60 )
			sceneNode->setFrameLoop ( 0 , 0 );
	}
	std::list<Splash>::iterator it = splashActive.begin();
	int i = 0;
	while ( it != splashActive.end() ) {

		bool del = false;
		bool cont = false;
		irr::core::list<irr::scene::ISceneNodeAnimator*> AnimList = (*it).getSceneNode()->getAnimators();
		irr::core::list<irr::scene::ISceneNodeAnimator*>::Iterator it2 = AnimList.begin();
		while ( it2 != AnimList.end() ) {

			if ( (*it2)->hasFinished() ) {

				(*it).getSceneNode()->removeAnimator(*it2);

				if ( (*it).getPos() >= 0 ) {

					if ( splashDamierVec[(*it).getPos()].getLevel() > 0 || combo == -1 ) {
						sceneManager->addToDeletionQueue ( (*it).getSceneNode() );
						IncreaseSplash ( (*it).getPos() );
						del = true;
					}
					else if ( (*it).Stuck() ) {
						sceneManager->addToDeletionQueue ( (*it).getSceneNode() );
						del = true;
					}
					else {

						(*it).Animate(sceneManager);
					}
				}
				else
					del=true;
			}
			++it2;
		}
		if ( del )
			it = splashActive.erase ( it );
		else
			++it;
	}
	if ( splashActive.size() == 0 ) {

		if ( combo > 0 ) {

			irr::scene::IMesh* splashMesh = sceneManager->getMesh ( "resources/models/splash3.obj" );
			irr::scene::ISceneNode* sceneNode = sceneManager->addMeshSceneNode ( splashMesh );
			sceneNode->setMaterialTexture ( 0 , videoDriver->getTexture ( "resources/textures/fabric.jpg" ) );
			sceneNode->setMaterialFlag ( irr::video::EMF_LIGHTING , true );
			sceneNode->setID ( 0x0 );

			for ( int i = 0 ; i < combo ; ++i ) {

				sceneNode->setPosition ( irr::core::vector3df ( 0 , splashMagazine.size()*25 , -100 ) );
				splashMagazine.push_back ( Splash ( -(splashMagazine.size()+1) , sceneNode->clone() ) );

			}

			sceneManager->addToDeletionQueue ( sceneNode );
		}
		combo = -1;
		if ( Empty() )
			Init_Game();
		irr::core::line3df ray = sceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates ( receiver.GetMouseState().Position , camera );
		currentNode = sceneManager->getSceneCollisionManager()->getSceneNodeFromRayBB ( ray , 0x1 );
		if ( currentNode != NULL ) {

			if ( !receiver.GetMouseState().LeftButtonDown )
				click = false;
			if ( receiver.GetMouseState().LeftButtonDown && !click && splashMagazine.size() != 0 ) {

				click = true;
				int i = atoi ( currentNode->getName() );
				Splash s = splashMagazine.front();
				splashMagazine.pop_front();
				irr::scene::ISceneNodeAnimator* anim = sceneManager->createFlyStraightAnimator ( irr::core::vector3df ( 0 , 0 , 0 ) , irr::core::vector3df ( -45 + i%4 * 30 , 45 - i/4 * 30 , 5 ) , 1000 );
				s.getSceneNode()->addAnimator ( anim );
				s.setPos ( i );
				splashActive.push_back ( s );
				for ( std::list<Splash>::iterator it = splashMagazine.begin() ; it != splashMagazine.end() ; it++ ) {

					irr::scene::ISceneNodeAnimator* anim = sceneManager->createFlyStraightAnimator ( irr::core::vector3df ( 0 , - ( (*it).getPos() + 1 ) * 10 , 0 ) , irr::core::vector3df ( 0 , - ( (*it).getPos() + 2 ) * 10 , 0 ) , 1000 );
					(*it).getSceneNode()->addAnimator ( anim );
					(*it).setPos ( (*it).getPos() + 1 );
					Splash active ( *it );
					splashActive.push_back ( active );
				}
			}
		}
	}
}

bool SplashBack::Empty () {

	for ( int i = 0 ; i < 16 ; ++i ) {

		if ( splashDamierVec[i].getLevel() != 0 )
			return false;
	}
	return true;
}

void SplashBack::Render() {

	videoDriver->beginScene ( true , true , irr::video::SColor ( 0 , 0 , 0 , 0 ) );
	sceneManager->drawAll();
	guiEnv->drawAll();
	irr::core::stringw text = L"Level ";
	text += irr::core::stringw(level);
	font->draw(text,irr::core::rect<s32>(130,10,300,50),irr::video::SColor(255,255,255,255));
	videoDriver->endScene();
}

bool SplashBack::Run() {

	return device->run();
}

void SplashBack::Drop() {

	device->drop();
}
