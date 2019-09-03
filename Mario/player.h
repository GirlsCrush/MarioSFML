#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include <vector>

using namespace sf;
using namespace std;


enum xDirection { LEFT = -1, RIGHT = 1};
enum yDirection { UP = -1, DOWN = 1 };
enum Direction { X = 0, Y = 1 };
class player
{
	float dx = 0, dy = 0;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;

public:
	float offsetX = 0, offsetY = 0;
	void update(float, vector<enemy>);
	void moveX(xDirection);
	void moveY(yDirection);	
	bool onGround = true;
	bool isDead = false;
	Sprite getSprite();
	FloatRect getRect();
	void collision(Direction);
	void collisionEnemies(vector<enemy>);
	player(Texture &);
	~player();
};



