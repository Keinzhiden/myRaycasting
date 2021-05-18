#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <map>
#include <chrono>
#include <vector>
using namespace std;

class Raycaster {

public:
    Raycaster();
    ~Raycaster() = default;
    vector<vector<int>> map
    {
        {1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1},
        {1,0,1,1,0,0,1},
        {1,0,1,0,0,0,1},
        {1,0,0,0,1,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1}
    };
    sf::Color WallColor;
    sf::Color FloorColor;
    sf::Vector2i mapSize{ 7,7 };
    sf::Vector2f cellSize{ 40,40 };
    sf::Vector2f playerPosition{ 40,40 };
    sf::Vector2f otherPosition{ 40,40 };
    sf::Vector2i mousePosition;
    float playerSpeed;
    sf::Vector2i playerInput;
    static const unsigned int xWindowWidth = 1500;
    static const unsigned int yWindowHeight = 1000;
    static const int sizeColumn = 4;
    double PI = 3.141592;
    float visionAngle = 60;
    float visionDirAngle = 0.0f;
    static const int nbOfRay = xWindowWidth / sizeColumn;
    const float rotateVisionSpeed = 0.1f;
    double tabLenght[nbOfRay];

    sf::Sprite spriteMap;
    sf::Texture textureMap;
    sf::Image imageMap;

    sf::Sprite spriteView;
    sf::Texture textureView;
    sf::Image imageView;

    sf::Vector2f rayStart;
    sf::Vector2f vRaydir;

    sf::Sprite drawMap();
    sf::Sprite drawView();
    void moveotherPositionTo(sf::Vector2f newPosition);
    void movePlayerOnInput(sf::Vector2i dir);
    void rotatePlayerOnMouse(sf::Vector2i mousePos, sf::RenderWindow& window);
    void setPixelsColorFromMap(int i, int j, int TileValue);
    void setPixelsColorForView(int i);
    sf::Vector2f getPlayerPos();
    sf::Vector2f getOtherPos();

    sf::Vector2f CalcRay(sf::Vector2f StartPosition = {0,0}, sf::Vector2f vDir = { 0,0 });
    void CalcAllRayOfVision();
    sf::Vector2f CalcOneRayOfVision(int indexRay);

    
private:

};