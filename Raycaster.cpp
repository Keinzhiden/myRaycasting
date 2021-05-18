#pragma once 

#include "Raycaster.h"

Raycaster::Raycaster() {
    imageMap.create(1500, 1000, sf::Color::Black);
    imageView.create(1500, 1000, sf::Color::Black);
    WallColor = sf::Color(sf::Uint8(0), sf::Uint8(0), sf::Uint8(255), sf::Uint8(255));

}

sf::Sprite Raycaster::drawMap() {
	for (auto i = 0; i < mapSize.x; i++) {
		for (auto j = 0; j < mapSize.y; j++) {
            setPixelsColorFromMap(i,j,map[i][j]);
		}
	}
    textureMap.loadFromImage(imageMap);
    spriteMap.setTexture(textureMap);
    return spriteMap;
}

sf::Sprite Raycaster::drawView() {
    imageView.create(1500, 1000, sf::Color::Black);
    for (auto i = 0; i < nbOfRay; i++) {
        setPixelsColorForView(i);
    }
    textureView.loadFromImage(imageView);
    spriteView.setTexture(textureView);
    return spriteView;
}

void Raycaster::setPixelsColorForView(int i) {
    sf::Color col = WallColor;
    double lenght = tabLenght[i];
    for (unsigned int k = 0; k < sizeColumn; k++) {
        //cout << i * sizeColumn + k << " / "<< int(lenght) <<endl;
        if (lenght < 50) {
            col.a = 240;
        }
        else if (lenght < 100) {
            col.a = 210;
        }
        else if (lenght < 150) {
            col.a = 180;
        }
        else if (lenght < 200) {
            col.a = 120;
        }
        else if (lenght < 250) {
            col.a = 60;
        }
        else {
            col.a = 0;
        }
        
        //if (lenght < 0.0)lenght = lenght *-1;
        float lineHeight = yWindowHeight /(float)lenght * 32;
        if (lineHeight > (float)yWindowHeight) lineHeight = yWindowHeight ;
        int lineOffset = int((int)yWindowHeight/2 - lineHeight / 2) ;
        //cout << lenght << " / " << lineHeight << endl;
        for (unsigned int l = 0; l < (int)lineHeight; l++) {
            
            imageView.setPixel(i* sizeColumn + k,lineOffset + l, col);
        }
    }
}

void Raycaster::setPixelsColorFromMap(int i, int j, int TileValue) {
    sf::Color col = sf::Color::Black;
    if (TileValue == 1)col = sf::Color::White;
    for (unsigned int k = 0; k < (cellSize.x); k++) {
        for (unsigned int l = 0; l < (cellSize.y); l++) {
            imageMap.setPixel(i * cellSize.x + k, j * cellSize.y + l, col);
        }
    }
}

void Raycaster::moveotherPositionTo(sf::Vector2f newPosition) {
    otherPosition = newPosition;
}
void Raycaster::movePlayerOnInput(sf::Vector2i dir) {
    sf::Vector2f movement = { 0,0 };
    if (dir.y > 0) {
        movement.x = -cos(visionDirAngle * PI / 180);
        movement.y = -sin(visionDirAngle * PI / 180);
    }
    else if (dir.y < 0) {
        movement.x = cos(visionDirAngle * PI / 180);
        movement.y = sin(visionDirAngle * PI / 180);
    }
    if (dir.x > 0) {
        movement.x += cos((90+visionDirAngle) * PI / 180);
        movement.y += sin((90 + visionDirAngle) * PI / 180);
    }
    else if (dir.x < 0) {
        movement.x += -cos((90 + visionDirAngle) * PI / 180);
        movement.y += -sin((90 + visionDirAngle) * PI / 180);
    }
    playerPosition.x += movement.x;
    playerPosition.y += movement.y;
}

sf::Vector2f Raycaster::getPlayerPos() {
    return playerPosition;
}

sf::Vector2f Raycaster::getOtherPos() {
    return otherPosition;
}

void Raycaster::CalcAllRayOfVision() {

    float stepBetweenRaysInDeg = visionAngle / nbOfRay;

    //(visionDirAngle - visionAngle) / 2 * PI / 180
    //sf::Vector2f headingVector{ cos((visionDirAngle - visionAngle + stepBetweenRaysInDeg * 0) / 2 * PI / 180),sin((visionDirAngle - visionAngle + stepBetweenRaysInDeg * 0) / 2 * PI / 180) };
    for (auto i = 0; i < nbOfRay; i++) {
        sf::Vector2f thisRay = CalcRay(playerPosition, sf::Vector2f{ (float)cos((((visionDirAngle - visionAngle / 2)) + stepBetweenRaysInDeg * i) * PI / 180),(float)sin((((visionDirAngle - visionAngle / 2)) + stepBetweenRaysInDeg * i) * PI / 180) });
        if (thisRay.x != 0 && thisRay.y != 0) {
            double length = sqrt(((thisRay.x - playerPosition.x) * (thisRay.x - playerPosition.x)) + ((thisRay.y - playerPosition.y) * (thisRay.y - playerPosition.y)));
            int factor = -1;
            int offset = 30;
            if (((visionDirAngle - visionAngle / 2) + stepBetweenRaysInDeg * i) < visionDirAngle) {
                factor = 1;
                offset = 0;
            }
            //cout << ((visionDirAngle - visionAngle / 2) + stepBetweenRaysInDeg * i) << " / " << ((((visionAngle / 2)) - stepBetweenRaysInDeg * i) * factor) << endl;
            length = cos(((((visionAngle / 2)) - stepBetweenRaysInDeg * i) * factor) * PI / 180) * length;
            tabLenght[i] = length;
        }
        else {
            tabLenght[i] = 300;
        }
        
    }
    cout << "Green : " << tabLenght[0] << " | Yellow " << tabLenght[149] << endl;
}

sf::Vector2f Raycaster::CalcOneRayOfVision(int indexRay) {
    int nbOfRay = 1500 / sizeColumn;
    float stepBetweenRaysInDeg = visionAngle / nbOfRay ;
    double PI = 3.141592;
    //(visionDirAngle - visionAngle) / 2 * PI / 180
    //sf::Vector2f headingVector{ cos((visionDirAngle - visionAngle + stepBetweenRaysInDeg * 0) / 2 * PI / 180),sin((visionDirAngle - visionAngle + stepBetweenRaysInDeg * 0) / 2 * PI / 180) }; 
    return CalcRay(playerPosition, sf::Vector2f{ (float)cos((((visionDirAngle - visionAngle/ 2)) + stepBetweenRaysInDeg * indexRay) * PI / 180),(float)sin((((visionDirAngle - visionAngle/ 2)) + stepBetweenRaysInDeg * indexRay) * PI / 180) });
}

void Raycaster::rotatePlayerOnMouse(sf::Vector2i mousePos, sf::RenderWindow &window) {
    sf::Vector2i centerScreenPos = { xWindowWidth / 2,yWindowHeight / 2 };
    if (mousePos.x != centerScreenPos.x) {
        if (mousePos.x > centerScreenPos.x) {
            //if (visionDirAngle - 1 < -180) {
            //    visionDirAngle = visionDirAngle + 359;
            //}
            //else {
                visionDirAngle = visionDirAngle + (mousePos.x - centerScreenPos.x)/10;
           // }
            
        }
        else {
            visionDirAngle = visionDirAngle + (mousePos.x - centerScreenPos.x)/10;
        }
        sf::Mouse::setPosition(centerScreenPos,window);
    }
    mousePosition = mousePos;
}

sf::Vector2f Raycaster::CalcRay(sf::Vector2f StartPosition,sf::Vector2f vDir) {
    rayStart = { StartPosition.x / cellSize.x,StartPosition.y / cellSize.y };
    sf::Vector2f rayEnd = { otherPosition.x / cellSize.x,otherPosition.y / cellSize.y };
    //vRaydir = { vDir.x * 3,vRaydir.y * 3 };
    //vRaydir = vDir * 3.0;
    vRaydir = vDir;

    double length = sqrt((vRaydir.x * vRaydir.x) + (vRaydir.y * vRaydir.y));
    if (length != 0) vRaydir = sf::Vector2f(vRaydir.x / length, vRaydir.y / length);


    sf::Vector2f vRayUnitStepSize = { sqrt(1 + (vRaydir.y / vRaydir.x) * (vRaydir.y / vRaydir.x)),sqrt(1 + (vRaydir.x / vRaydir.y )* (vRaydir.x / vRaydir.y)) };


    sf::Vector2i mapCheck = { (int)floor(rayStart.x),(int)floor(rayStart.y) };
    sf::Vector2f vRayLenght;
    sf::Vector2f vStep;

    if (vRaydir.x < 0) {
        vStep.x = -1;
        vRayLenght.x = (rayStart.x - float(mapCheck.x)) * vRayUnitStepSize.x;
    }
    else {
        vStep.x = 1;
        vRayLenght.x = (float(mapCheck.x + 1) - rayStart.x) * vRayUnitStepSize.x;
    }
    if (vRaydir.y < 0) {
        vStep.y = -1;
        vRayLenght.y = (rayStart.y - float(mapCheck.y)) * vRayUnitStepSize.y;
    }
    else{
        vStep.y = 1;
        vRayLenght.y = (float(mapCheck.y + 1) - rayStart.y) * vRayUnitStepSize.y;
    }
    

    //cout << "RayLenght x :" << vRayLenght.x << " y : " << vRayLenght.y << endl;// " | " << distance << " -- " << vRayUnitStepSize.x << ":" << vRayUnitStepSize.y << endl;

    bool isTileFound = false;
    float maxDistance = 300.0f;
    float distance = 0.0f;
    while (!isTileFound && distance < maxDistance) {
        if (vRayLenght.x < vRayLenght.y) {
            mapCheck.x += vStep.x;
            distance = vRayLenght.x;
            vRayLenght.x += vRayUnitStepSize.x;
        }
        else {
            mapCheck.y += vStep.y;
            distance = vRayLenght.y;
            vRayLenght.y += vRayUnitStepSize.y;
        }
        if ((mapCheck.x >= 0 && mapCheck.x < mapSize.x) && (mapCheck.y >= 0 && mapCheck.y < mapSize.y))
        {
            if (map[mapCheck.x][mapCheck.y] == 1) {
                isTileFound = true;
                //cout << "Inter x :" << mapCheck.x << " y : " << mapCheck.y << " | " << distance << " -- " <<vRayUnitStepSize.x <<":" << vRayUnitStepSize.y << endl;
            }
        }
        
        
    }

    if (!isTileFound) {
        return sf::Vector2f(0,0);
    }
    else {
        return sf::Vector2f((playerPosition + sf::Vector2f( vRaydir.x * cellSize.x,vRaydir.y * cellSize.y)  *distance));
    }


}

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}