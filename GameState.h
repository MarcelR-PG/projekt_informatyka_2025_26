#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "BlockData.h"
#include "Paletka.h"
#include "Pilka.h"
#include "Brick.h"

class GameState
{
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameState(const Paletka& p, const Pilka& pi, const std::vector<Brick>& b);

    sf::Vector2f getPaddlePosition() const { return paddlePosition; }
    sf::Vector2f getBallPosition() const { return ballPosition; }
    sf::Vector2f getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }

    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void apply(Paletka& p, Pilka& b, std::vector<Brick>& bricks);
};
