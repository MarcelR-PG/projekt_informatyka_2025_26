#include "GameState.h"
#include <fstream>
#include <iostream>

GameState::GameState(const Paletka& p, const Pilka& pi, const std::vector<Brick>& b)
{
    paddlePosition = sf::Vector2f(p.getX(), p.getY());
    ballPosition = sf::Vector2f(pi.getX(), pi.getY());
    ballVelocity = sf::Vector2f(pi.getVx(), pi.getVy());

    blocks.clear();
    for (const auto& brick : b)
    {
        BlockData data;
        data.x = brick.getPosition().x;
        data.y = brick.getPosition().y;
        data.hp = brick.getHP();
        blocks.push_back(data);
    }
}

bool GameState::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& block : blocks)
    {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;
    int blocksCount;

    // Paletka
    file >> label >> paddlePosition.x >> paddlePosition.y;

    // Pilka
    file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;

    // Bloki
    file >> label >> blocksCount;
    blocks.clear();

    for (int i = 0; i < blocksCount; ++i)
    {
        float x, y;
        int hp;
        file >> x >> y >> hp;
        blocks.push_back({ x, y, hp });
    }

    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Brick>& bricks)
{
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    bricks.clear();
    sf::Vector2f brickSize(60.f, 20.f);

    for (const auto& data : blocks)
    {
        bool destroyed = (data.hp <= 0);
        Brick brick(sf::Vector2f(data.x, data.y), brickSize, data.hp, destroyed);
        bricks.push_back(brick);
    }
}
