#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <Game.h>
#include <sstream>

using namespace sf;

int main()
{
    Arkanoid::Game game;
    game.window.create(VideoMode(800, 600), "Game");
    game.window.setFramerateLimit(60);

    game.music.openFromFile("Hypnotrans.wav");

    game.music.play();
    game.music.setLoop(true);

    game.LevelDifficulty();

    // Load Textures
    game.ballTexture.loadFromFile("Ball.png");
    game.stickTexture.loadFromFile("Stick.png");
    game.blockTexture.loadFromFile("Block.png");

    game.ball.sprite.setTexture(game.ballTexture);
    game.stick.setTexture(game.stickTexture);
    game.blocks.resize(game.countOfBlocks);
    for (int i = 0; i < game.blocks.size(); i++) game.blocks[i].setTexture(game.blockTexture);

    //Init fatBlockLives
    game.fatBlockLives.resize(game.blocks.size());

    for (int j = 0; j < game.blocks.size(); j += 4)
    {
        game.fatBlockLives[j] = 2;
    }

    game.SetStartPosition();

    while (game.window.isOpen() == true)
    {
        Event ev;
        while (game.window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                game.window.close();
            }
        }

        game.window.clear();
        

        #pragma region Game process

        if (game.ball.sprite.getPosition().y > 570)
        {
            game.ball.speed = 0;
            game.PlayerLives--;
            game.PointsToWin = 0;
            for (int i = 0; i < game.blocks.size(); i += 4) game.fatBlockLives[i] = 2;
            game.SetStartPosition();
        }

        if (Mouse::isButtonPressed(Mouse::Left) == true)
        {
            game.ball.Start(game.startSpeed, Vector2f(0, -1));
        }

        game.ball.Move(Vector2i(0, 0), Vector2i(800, 600));

        game.ball.CheckCollision(game.stick, "Stick");
        for (int i = 0; i < game.blocks.size(); i++)
        {
            if (game.ball.CheckCollision(game.blocks[i], "Block") == true)
            {
                if (i % 4 == 0)
                {
                    game.fatBlockLives[i]--;
                    if (game.fatBlockLives[i] == 0)
                    {
                        game.blocks[i].setPosition(Vector2f(1000, 1000));
                        game.PointsToWin += 2;
                        break;
                    }
                }

                else
                {
                    game.blocks[i].setPosition(Vector2f(1000, 1000));
                    game.PointsToWin++;
                    break;
                }
            }
        }

        game.stick.setPosition(Vector2f(Mouse::getPosition(game.window).x - game.stick.getTextureRect().width * 0.5f, game.stick.getPosition().y));

        #pragma endregion


        #pragma region Drawing of game objects

        game.text = new Text("Your lives: " + to_string(game.PlayerLives), game.font);
        game.text->setPosition(Vector2f(630, -5));
        game.window.draw(*(game.text));

        game.window.draw(game.ball.sprite);
        game.window.draw(game.stick);
        for (int i = 0; i < game.blocks.size(); i++)
            game.window.draw(game.blocks[i]);

        // Lose
        if (game.PlayerLives == 0)
        {
            game.window.clear();
            game.text = new Text("You lost!\nPress left mouse button to exit menu.", game.font);
            game.text->setPosition(Vector2f(115, 200));
            game.window.draw(*(game.text));
            game.window.display();

            while (Mouse::isButtonPressed(Mouse::Left) == false) game.PlayerLives = 3;
            game.window.clear();
            game.LevelDifficulty();
            game.blocks.clear();
            game.blocks.resize(game.countOfBlocks);
            for (int i = 0; i < game.blocks.size(); i++) game.blocks[i].setTexture(game.blockTexture);

            //Init fatBlockLives
            game.fatBlockLives.clear();
            game.fatBlockLives.resize(game.blocks.size());
            for (int i = 0; i < game.blocks.size(); i += 4) game.fatBlockLives[i] = 2;

            game.SetStartPosition();
        }

        //Win
        if (game.PointsToWin == (game.countOfBlocks / 4) * 2 + game.countOfBlocks - (game.countOfBlocks / 4))
        {
            game.window.clear();
            game.text = new Text("You won!\nPress left mouse button to exit menu.", game.font);
            game.text->setPosition(Vector2f(115, 200));
            game.window.draw(*(game.text));
            game.window.display();
            while (Mouse::isButtonPressed(Mouse::Left) == false)

            game.PointsToWin = 0;
            game.ball.speed = 0;
            game.PlayerLives = 3;

            game.window.clear();
            game.LevelDifficulty();
            game.blocks.clear();
            game.blocks.resize(game.countOfBlocks);
            for (int i = 0; i < game.blocks.size(); i++) game.blocks[i].setTexture(game.blockTexture);

            //Init fatBlockLives
            game.fatBlockLives.clear();
            game.fatBlockLives.resize(game.blocks.size());
            for (int i = 0; i < game.blocks.size(); i += 4) game.fatBlockLives[i] = 2;

            game.SetStartPosition();
        }

        #pragma endregion

        game.window.display();
    }
}
