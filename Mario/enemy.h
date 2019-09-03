#pragma once
#include <SFML/Graphics.hpp>
#include "defs.h"
#include "map.h"

using namespace sf;
using namespace std;

class enemy
{
	float dx = 5;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;
	float walked;
	void collision();
public:
	void update(float);
	enemy(Texture &);
	Sprite getSprite();
	FloatRect getRect();
	bool onGround = true;
};


