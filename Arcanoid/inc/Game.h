#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Ball.h>
#include <math.h>
#include <vector>
#include <SFML/Audio.hpp>

using namespace sf;

namespace Arkanoid
{
    class Game
    {
    public:

        RenderWindow window;
        int widthBetweenBlocks = 40;
        int heightBetweenBlocks = 32;
        int indentX = 75;
        int indentY = 40;

        int countOfBlocks; // This number must have an integer root
        int startSpeed = 10;
        int PlayerLives = 3;
        int PointsToWin = 0;

        vector <int> fatBlockLives;

        Music music;

        Font font;
        Text* text;

        Sprite stick;
        vector <Sprite> blocks;

        Texture ballTexture;
        Texture stickTexture;
        Texture blockTexture;

        Ball ball;

        void LevelDifficulty()
        {
            font.loadFromFile("ofont.ru_Sweet Mavka Script.ttf");
            text = new Text("Choose the difficulty:\nPress\"A\" for normal - 1 Level\nPress\"F\" for hard - 2 Level", font);
            text->setPosition(Vector2f(150, 200));

            window.draw(*text);
            window.display();
            while (window.isOpen() == true)
            {
                if (Keyboard::isKeyPressed(Keyboard::A) == true)
                {
                    countOfBlocks = 64;
                    widthBetweenBlocks = 40;
                    heightBetweenBlocks = 32;
                    startSpeed = 8;
                    break;
                }

                if (Keyboard::isKeyPressed(Keyboard::F) == true)
                {
                    countOfBlocks = 36;
                    widthBetweenBlocks = 70;
                    heightBetweenBlocks = 50;
                    startSpeed = 14;
                    break;
                }
            }
        }
        void SetStartPosition()
        {
            int index = 0;
            for (int y = 0; y < pow(countOfBlocks, 0.5f); y++)
            {
                for (int x = 0; x < pow(countOfBlocks, 0.5f); x++)
                {
                    blocks[index].setPosition(Vector2f(x * (blocks[index].getTextureRect().width + widthBetweenBlocks) + indentX,
                        y * (blocks[index].getTextureRect().height + heightBetweenBlocks) + indentY));
                    index++;
                }
            }
            stick.setPosition(Vector2f(400, 550));
            ball.sprite.setPosition(Vector2f(375, 450));
        }
    };
}


