#pragma once

class Bird
{
    float x;
    float y;

    float spriteSize;
    float fallingSpeed;
    
public:
    float X() { return x; }
    float Y() { return y; }
    float SpriteSize() { return spriteSize; }
    float FallingSpeed() { return fallingSpeed; }

public:
    Bird()
    {
        x = 0;
        y = 0;
        spriteSize = 30;
        fallingSpeed = 0.1f;
    }
public:
    Bird(float newX, float newY)
    {
        x = newX;
        y = newY;
        spriteSize = 30;
        fallingSpeed = 0.1f;
    }

public:
    void fall(float gravity)
    {
        fallingSpeed += gravity;
        y += fallingSpeed;
    }

public:
    void jump()
    {
        fallingSpeed = -7;
    }
};