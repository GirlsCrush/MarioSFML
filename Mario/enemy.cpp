#include "enemy.h"



void enemy::collision()
{
	for (int i = int(rect.left) / TILE_WIDTH; i <= int(rect.left + PLAYER_WIDTH - EPS) / TILE_WIDTH; i++)
		for (int j = int(rect.top) / TILE_HEIGHT; j <= int(rect.top + PLAYER_HEIGHT - EPS) / TILE_HEIGHT; j++)
		{
			if (TileMap[j][i] == 'P' || TileMap[j][i] == 'r' || TileMap[j][i] == '0' || TileMap[j][i] == 't')
			{
				if (dx < 0)
					rect.left = (i + 1) * TILE_WIDTH;
				else 
					rect.left = i * TILE_WIDTH - PLAYER_WIDTH;

				dx *= -1;
				walked = 0;
			}
		}
}

void enemy::update(float time)
{
	rect.left += dx * time;
	walked += dx * time;
	collision();
	if (abs(walked) > 100)
	{
		dx *= -1;
		walked = 0;
	}
	if(dx > 0)
		sprite.setTextureRect(IntRect(15, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	else
		sprite.setTextureRect(IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));

	sprite.setPosition(rect.left, rect.top);
}

enemy::enemy(Texture &image)
{
	sprite.setTexture(image);
	rect = FloatRect(6 * TILE_WIDTH, (TILE_MAP_HEIGHT - 3) * TILE_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
	sprite.setTextureRect(IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	onGround = true;
	currentFrame = 0;
}


Sprite enemy::getSprite()
{
	return sprite;
}


FloatRect enemy::getRect()
{
	return rect;
}
