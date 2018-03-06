#include "StarTrekBulletsManager.h"
#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"
#include "ExampleGame.h"




StarTrekBulletsManager::StarTrekBulletsManager()
{
}


StarTrekBulletsManager::~StarTrekBulletsManager()
{
}

void StarTrekBulletsManager::shoot(Fighter* owner, Vector2D p, Vector2D v) { //Comprueba el estado actual de las balas (Hay alguna inactiva?)
	pair<bool, Bullets*> check = bullets_.getObjectPool();

	if (check.first) { //Si hay alguna inactiva, la activa
		check.second->setActive(true);
		check.second->setPosition(p);
		check.second->setVelocity(v);
	}
	else { //Si no, crea una nueva
		newShoot(check.second, v, p);
	}
}

void StarTrekBulletsManager::update(Uint32 time) { //Esto s�lo actualiza el estado de las balas
	for (int i = 0; i < bullets_.size(); i++) {
		if ((*bullets_.getItem(i))->isActive()) {
			static_cast<Bullets*>(*bullets_.getItem(i))->update(time);
		}
	}
}

pair<bool, Bullets*> StarTrekBulletsManager::checkBullets() {
	Uint32 i = 0;
	bool encontrado = false;
	Bullets* aux;
	while (i < bullets_.size()) {
		if (!(*bullets_.getItem(i))->isActive()) {
			encontrado = true;
			aux = (*bullets_.getItem(i));
		}
		i++;
	}
	pair<bool, Bullets*> resultado(encontrado, aux);
	return resultado;
}

void StarTrekBulletsManager::render(Uint32 time) {
	for (int i = 0; i < bullets_.size(); i++) {
		static_cast<Bullets*>(*bullets_.getItem(i))->render(time);
	}
}

void StarTrekBulletsManager::newShoot(Bullets* bull, Vector2D vel, Vector2D pos) {
	//Creamos los metodos basicos de render y fisicas
	FillRectRenderer* fillRect = new FillRectRenderer();
	BasicMotionPhysics* motion = new BasicMotionPhysics();

	//a�adimos dichos metodos al Container
	bull->addPhysicsComponent(motion);
	bull->addRenderComponent(fillRect);

	//establecemos su tama�o y lo a�adimos a la lista de balas
	bull->setHeight(5);
	bull->setWidth(5);
	bull->setVelocity(vel);
	bull->setPosition(pos);
	//bullets.addNewItem(newBullet);
	static_cast<ExampleGame*>(game)->pushObject(bull);
}

void StarTrekBulletsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		break;
	case ROUND_END:
		break;
	case BULLET_ASTEROID_COLISION:
		break;
	case BULLET_FIGHTER_COLLISION:
		break;
	case FIGHTER_SHOOT:
		break;
	}
}
