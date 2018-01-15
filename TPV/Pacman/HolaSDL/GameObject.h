#pragma once
#include <fstream>
#include <SDL.h>
using namespace std;
class Game;
class GameObject
{
protected:
	Game* game;
	
public:
	virtual void render()=0;
	virtual void render(bool)=0;
	virtual void update()=0;
	virtual void loadFromFile(ifstream& file)=0;
	virtual void saveToFile(ofstream& file)=0;
	//virtual bool handleEvent(SDL_Event& e)=0;
};

