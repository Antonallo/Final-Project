#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace Arkanoid
{
	class Ball
	{
	public:
		Sprite sprite;
		float speed = 0;

		void Start(float speed, Vector2f direction)
		{
			if (this->speed != 0) return;

			this->speed = speed;
			this->direction = direction;
		}

		void Move(Vector2i boundsPos, Vector2i boundsSize)
		{
			sprite.setPosition(sprite.getPosition() + direction * speed);

			if (sprite.getPosition().x > boundsSize.x - sprite.getTexture()->getSize().x || sprite.getPosition().x < boundsPos.x)
			{
				direction.x *= -1;
			}

			if (sprite.getPosition().y < boundsPos.y)
			{
				direction.y *= -1;
			}
		}

		bool CheckCollision(Sprite sprite, string tag)
		{
			if (this->sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) == true)
			{
				if (tag == "Stick")
				{
					direction.y = -1;
					float f = ((this->sprite.getPosition().x + this->sprite.getTexture()->getSize().x * 0.5f) - (sprite.getPosition().x + sprite.getTexture()->getSize().x * 0.5f)) / sprite.getTexture()->getSize().x;
					direction.x = f * 2;
				}

				if (tag == "Block")
				{
					direction.y *= -1;
				}

				return true;
			}
			return false;
		}

	private:
		Vector2f direction;
	};
}
