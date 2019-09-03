#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "defs.h"

using namespace std;
using namespace sf;

#define offsetX p.offsetX
#define offsetY p.offsetY

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario Remake");
	Texture mapT;
	mapT.loadFromFile("Mario_tileset.png");

	Sprite rectangle;
	rectangle.setTexture(mapT);

	std::vector<enemy> enemies;
	//enemies.push_back(enemy(mapT));
	player p(mapT);

	Clock clock;

	while (window.isOpen())
	{
		sf::Event event;

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 500;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				p.moveX(LEFT);
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				p.moveX(RIGHT);
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (p.onGround)
				{
					p.moveY(UP);
					p.onGround = false;
				}
			}
		}

		for (int i = 0; i < enemies.size(); i++)
			enemies[i].update(time);

		p.update(time, enemies);

		window.clear(Color::Blue);
		for (int i = 0; i < TILE_MAP_HEIGHT; i++)
			for (int j = 0; j < TILE_MAP_WIDTH; j++) {
				if (TileMap[i][j] == 'P')  rectangle.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

				if (TileMap[i][j] == 'k')  rectangle.setTextureRect(IntRect(143, 112, 16, 16));

				if (TileMap[i][j] == 'c')  rectangle.setTextureRect(IntRect(143 - 16, 112, 16, 16));

				if (TileMap[i][j] == 't')  rectangle.setTextureRect(IntRect(0, 47, 32, 95 - 47));

				if (TileMap[i][j] == 'g')  rectangle.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

				if (TileMap[i][j] == 'G')  rectangle.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

				if (TileMap[i][j] == 'd')  rectangle.setTextureRect(IntRect(0, 106, 74, 127 - 106));

				if (TileMap[i][j] == 'w')  rectangle.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

				if (TileMap[i][j] == 'r')  rectangle.setTextureRect(IntRect(143 - 32, 112, 16, 16));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

				rectangle.setPosition(j * TILE_WIDTH - offsetX, i * TILE_HEIGHT - offsetY);
				window.draw(rectangle);
			}

		window.draw(p.getSprite());
		for (int i = 0; i < enemies.size(); i++)
			window.draw(enemies[i].getSprite());
		window.display();  
	}

	return 0;
}