#include "player.h"
#include "map.h"
#include "defs.h"

using namespace sf;

int ground = (TILE_MAP_HEIGHT - 3) * TILE_HEIGHT - PLAYER_HEIGHT;

void player::update(float time, vector<enemy> enemies)
{
	
	if (onGround)
	{
		bool tmp = false;
		for (int i = int(rect.left) / TILE_WIDTH; i < int(rect.left + PLAYER_WIDTH) / TILE_WIDTH; i++)
		{
			if (TileMap[int(rect.top + PLAYER_HEIGHT) / TILE_HEIGHT][i] == 'B' || TileMap[int(rect.top + PLAYER_HEIGHT) / TILE_HEIGHT][i] == 'P' || TileMap[int(rect.top + PLAYER_HEIGHT) / TILE_HEIGHT][i] == 'r')
				tmp = true;
		}
		onGround = tmp;
	}
	if (!onGround)
		dy += GRAVITY_C * time;
	rect.top += dy * time;

	collision(Y);

	rect.left += dx * time;
	collision(X);

	collisionEnemies(enemies);
	if (rect.top > ground)
	{
		rect.top = ground;
		dy = 0;
		onGround = true;
	}
	if (rect.left > WINDOW_WIDTH / 2 && rect.left < TILE_MAP_WIDTH * TILE_WIDTH - WINDOW_WIDTH / 2) offsetX = rect.left - WINDOW_WIDTH / 2;
	if (rect.top > WINDOW_HEIGHT / 2 && rect.top < TILE_MAP_HEIGHT * TILE_HEIGHT - WINDOW_HEIGHT / 2) offsetY = rect.top - WINDOW_HEIGHT / 2;
	if (rect.left >= TILE_MAP_WIDTH * TILE_WIDTH - WINDOW_WIDTH / 2) offsetX = TILE_MAP_WIDTH * TILE_WIDTH - WINDOW_WIDTH;
	if (rect.top >= TILE_MAP_HEIGHT * TILE_HEIGHT - WINDOW_HEIGHT / 2) offsetY = TILE_MAP_HEIGHT * TILE_HEIGHT - WINDOW_HEIGHT;

	currentFrame += FRAME_RATE * time;

	if (currentFrame > PLAYER_FRAMES) currentFrame = 0;

	if (dx > 0)
		sprite.setTextureRect(IntRect(110 + 31 * int(currentFrame), 144, PLAYER_WIDTH, PLAYER_HEIGHT));
	if (dx < 0)
		sprite.setTextureRect(IntRect(172 - 31 * int(currentFrame) + PLAYER_WIDTH, 144, -PLAYER_WIDTH, PLAYER_HEIGHT));

	dx = 0;
	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
}

void player::moveX(xDirection dir)
{
	dx = int(dir) * PLAYER_SPEED_X;
}

void player::moveY(yDirection dir)
{
	dy = int(dir) * PLAYER_SPEED_Y;
}

Sprite player::getSprite()
{
	return sprite;
}

FloatRect player::getRect()
{
	return rect;
}

void player::collision(Direction dir)
{
	for(int i = int(rect.left) / TILE_WIDTH; i <= int(rect.left + PLAYER_WIDTH - EPS) / TILE_WIDTH; i++)
		for (int j = int(rect.top) / TILE_HEIGHT; j <= int(rect.top + PLAYER_HEIGHT - EPS) / TILE_HEIGHT; j++)
		{
			if (TileMap[j][i] == 'P' || TileMap[j][i] == 'r' || TileMap[j][i] == '0' || TileMap[j][i] == 't')
			{
				if (dir == X)
				{
					if (dx < 0) rect.left = (i + 1) * TILE_WIDTH;
					if (dx > 0) rect.left = i * TILE_WIDTH - PLAYER_WIDTH;
				}
				if (dir == Y)
				{
					if (dy < 0)
					{
						rect.top = (j + 1) * TILE_HEIGHT;
						dy = 0;
					}
					if (dy > 0)
					{
						rect.top = j * TILE_WIDTH - PLAYER_HEIGHT;
						dy = 0;
						onGround = true;

					}
				}
			}
			if (TileMap[j][i] == 'k')
			{
				if (dir == X)
				{
					if (dx < 0) rect.left = (i + 1) * TILE_WIDTH;
					if (dx > 0) rect.left = i * TILE_WIDTH - PLAYER_WIDTH;
				}
				if (dir == Y)
				{
					if (dy < 0)
					{
						TileMap[j][i] = ' ';
					}
					if (dy > 0)
					{
						rect.top = j * TILE_WIDTH - PLAYER_HEIGHT;
						dy = 0;
						onGround = true;
					}
				}
			}
			if (TileMap[j][i] == 'c')
			{
				if (dir == X)
				{
					if (dx < 0) rect.left = (i + 1) * TILE_WIDTH;
					if (dx > 0) rect.left = i * TILE_WIDTH - PLAYER_WIDTH;
				}
				if (dir == Y)
				{
					if (dy < 0)
					{
						//CHANGES SHOULD BE DONE
						TileMap[j][i] = ' ';
					}
					if (dy > 0)
					{
						rect.top = j * TILE_WIDTH - PLAYER_HEIGHT;
						dy = 0;
						onGround = true;
					}
				}
			}
		}
}

void player::collisionEnemies(vector<enemy> enemies)
{

	for (int i = 0; i < enemies.size(); i++)
	{
		if (rect.intersects(enemies[i].getRect()))
		{
			if (dy > 0)
			{
				enemies.erase(enemies.begin() + i);
				i--;
			}
			else isDead = true;
		}
	}
}

player::player(Texture &image)
{
	sprite.setTexture(image);
	rect = FloatRect(TILE_WIDTH, (TILE_MAP_HEIGHT - 3) * TILE_HEIGHT - PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT);
	sprite.setTextureRect(IntRect(80, 144, PLAYER_WIDTH, PLAYER_HEIGHT));
	onGround = true;
	currentFrame = 0;
}


player::~player()
{
}
