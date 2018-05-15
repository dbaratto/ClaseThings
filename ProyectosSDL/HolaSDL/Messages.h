#pragma once

#include "sdl_includes.h"
#include "Vector2D.h"

enum MessageId {
	CONNECTED,
	JOINING_GAME,
	PLAYER_INFO,
	GAME_IS_READY,
	GAME_START,
	GAME_OVER,
	FIGHETR_STATE,
	FIGHTER_SHOOT,
	BULLET_FIGHTER_COLLISION,
	ADD_ASTEROID,
	TIME_HAS_PASSED,
	NEW_ASTEROID_INCOMING,
	ASTEROID_ADDED,
	ADDING_ASTEROID,
	BULLET_ASTEROID_COLLISION,
	FIGHTER_ASTEROID_COLLISION
};

typedef Uint16 header_t_;

// generic message -- note the size field
struct Message {
	Message(MessageId mType, header_t_ size = sizeof(Message)) :
			size_(size), mType_(mType) {
	}
	header_t_ size_;
	Uint8 mType_; // we have at most 256 different kinds of messages
};

// this message is sent by the server to the client to inform her
// with the user id.
struct ConnectedMsg: Message {
	ConnectedMsg(Uint8 clientId) :
			Message(CONNECTED, sizeof(ConnectedMsg)), clientId_(clientId) {
	}
	Uint8 clientId_;
};

// A message sent by a client when joining the game. In principle it
// should be processed by the MASTER client only
struct JoiningGameMsg: Message {
	JoiningGameMsg(Uint8 clientId) :
			Message(JOINING_GAME, sizeof(JoiningGameMsg)), clientId_(clientId) {
	}
	Uint8 clientId_;
};

// A message sent by a client when joining the game. In principle it
// should be processed by the MASTER client only
struct PlayerInfoMsg: Message {
	PlayerInfoMsg(Uint8 clientId) :
			Message(PLAYER_INFO, sizeof(PlayerInfoMsg)), clientId_(clientId) {
	}
	Uint8 clientId_;
};


struct FighterStateMsg: Message {
	FighterStateMsg(Uint8 clientId, Vector2D pos, Vector2D dir, Vector2D vel,
			double width, double height) :
			Message(FIGHETR_STATE, sizeof(FighterStateMsg)), clientId_(
					clientId), pos_(pos), dir_(dir), vel_(vel), width_(width), height_(
					height) {
	}
	Uint8 clientId_;
	Vector2D pos_;
	Vector2D dir_;
	Vector2D vel_;
	double width_;
	double height_;
};


struct FighterIsShootingMsg: Message {
	FighterIsShootingMsg(Uint8 fighterId, Vector2D bulletPosition,
			Vector2D bulletVelocity) :
			Message(FIGHTER_SHOOT, sizeof(FighterIsShootingMsg)), fighterId_(
					fighterId), bulletPosition_(bulletPosition), bulletVelocity_(
					bulletVelocity) {
	}
	Uint8 fighterId_;
	Vector2D bulletPosition_;
	Vector2D bulletVelocity_;
};


struct BulletFighterCollisionMsg: Message {
	BulletFighterCollisionMsg(Uint8 fighterId, Uint16 bulletId, Uint8 fbulletId) :
			Message(BULLET_FIGHTER_COLLISION, sizeof(BulletFighterCollisionMsg)), fighterId_(
					fighterId), bulletId_(bulletId), bulletOwnerId_(fbulletId) {
	}
	Uint8 fighterId_;
	// the following uniquely identify a bullet
	Uint16 bulletId_;
	Uint8 bulletOwnerId_;
};

struct BulletAsteroidCollisionMsg : Message {
	BulletAsteroidCollisionMsg(Uint16 bulletId, Uint8 fbulletId, Uint8 astPos) :
		Message(BULLET_ASTEROID_COLLISION, sizeof(BulletAsteroidCollisionMsg)), bulletId_(bulletId), bulletOwnerId_(fbulletId), astPos_(astPos) {
	}
	// the following uniquely identify a bullet
	Uint16 bulletId_;
	Uint8 bulletOwnerId_;
	Uint8 astPos_;
};

struct AsteroidFighterCollision : Message {
	AsteroidFighterCollision(Uint8 fighterId) :
		Message(FIGHTER_ASTEROID_COLLISION, sizeof(AsteroidFighterCollision)), fighterId_(fighterId) {
	}
	Uint8 fighterId_;
};

struct NewAsteroidMsg : Message {

	NewAsteroidMsg(MessageId mType, Vector2D astPosition, Vector2D astVelocity, Vector2D astDirection, int astWidth, int astHeight, bool astActive) : Message(mType, sizeof(NewAsteroidMsg)), astPosition_(astPosition), astVelocity_(astVelocity), astDirection_(astDirection),
		astWidth_(astWidth), astHeight_(astHeight), astActive_(astActive) {}

	Vector2D astPosition_; 
	Vector2D astVelocity_; 
	Vector2D astDirection_;
	int astWidth_;
	int astHeight_;
	bool astActive_;
};


// this value should be bigger than the size of all messages
#define MAX_MSG_SIZE 1000

