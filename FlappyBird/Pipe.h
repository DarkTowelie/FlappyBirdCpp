#pragma once


class Pipe
{
    float x;
    float y;
    float windowsSize;

    float spriteSizeX;
    float spriteSizeY;
public:
    bool passed;


public:
    float X() { return x; }
    float Y() { return y; }
    float WindowSize() { return windowsSize; }
    float SpriteSizeX() { return spriteSizeX; }
    float SpriteSizeY() { return spriteSizeY; }

public: Pipe(float newX, float newY)
{
    x = newX;
    y = newY;

    spriteSizeX = 45;
    spriteSizeY = 350;
    windowsSize = 150;
    passed = false;
}

public: void Move()
{
    x -= 2;
}
};