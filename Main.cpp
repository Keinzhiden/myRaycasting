#include "Raycaster.h"

int main(){

    const unsigned int xWidth = 1500;
    const unsigned int yHeight = 1000;
    sf::RenderWindow window(sf::VideoMode(xWidth, yHeight), "Raycaster C++/SFML");

    sf::Sprite spriteMinimap;
    sf::Sprite spriteView;
    Raycaster raycaster;
    sf::Vector2i dirInput;
    sf::CircleShape player;
    sf::CircleShape other;
    sf::CircleShape rayIntersectFirst;
    sf::CircleShape rayIntersectLast;
    sf::Vertex line[] =
    {
        sf::Vertex(player.getPosition()),
        sf::Vertex(other.getPosition())
    };

    line[0].color = sf::Color::Green;
    line[1].color = sf::Color::Green;
    line->color = sf::Color::Green;

    player.setRadius(10);
    other.setRadius(10);
    rayIntersectFirst.setRadius(7);
    rayIntersectLast.setRadius(7);
    player.setFillColor(sf::Color::Red);
    other.setFillColor(sf::Color::Blue);
    rayIntersectFirst.setFillColor(sf::Color::Green);
    rayIntersectLast.setFillColor(sf::Color::Yellow);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed )
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved) {
                raycaster.rotatePlayerOnMouse(sf::Mouse::getPosition(window),window);
            }
            if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Button::Left)) {
                //std

            }

            if (((event.type == sf::Event::KeyPressed)|| (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Up))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.y = -1;
                if (event.type == sf::Event::KeyReleased)dirInput.y = 0;

            }
            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Down)) {
                if (event.type == sf::Event::KeyPressed)dirInput.y = 1;
                if (event.type == sf::Event::KeyReleased)dirInput.y = 0;

            }
            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Left))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.x = -1;
                if (event.type == sf::Event::KeyReleased)dirInput.x = 0;
            }
            if (((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased)) && (event.key.code == sf::Keyboard::Right))
            {
                if (event.type == sf::Event::KeyPressed)dirInput.x = 1;
                if (event.type == sf::Event::KeyReleased)dirInput.x = 0;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {

            }

        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

        // convert it to world coordinates
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        raycaster.moveotherPositionTo(worldPos);
        raycaster.movePlayerOnInput(dirInput);

        raycaster.CalcAllRayOfVision();

        sf::Vector2f vIntersect = raycaster.CalcOneRayOfVision(0);
        rayIntersectFirst.setPosition(sf::Vector2f(vIntersect.x - rayIntersectFirst.getRadius(), vIntersect.y - rayIntersectFirst.getRadius()));
        vIntersect = raycaster.CalcOneRayOfVision(374);
        rayIntersectLast.setPosition(sf::Vector2f(vIntersect.x - rayIntersectLast.getRadius(), vIntersect.y - rayIntersectLast.getRadius()));
        player.setPosition(sf::Vector2f(raycaster.getPlayerPos().x - player.getRadius(), raycaster.getPlayerPos().y - player.getRadius()));
        other.setPosition(sf::Vector2f(raycaster.getOtherPos().x - other.getRadius(), raycaster.getOtherPos().y - other.getRadius()));
        window.clear();
        spriteView = raycaster.drawView();
        spriteMinimap = raycaster.drawMap();
        window.draw(spriteView);
        //window.draw(spriteMinimap);
        line[0] = raycaster.getPlayerPos(); 
        line[1] = raycaster.getOtherPos();
        window.draw(line, 2, sf::Lines);
        window.draw(player);
        window.draw(other);
        window.draw(rayIntersectFirst);
        window.draw(rayIntersectLast);
        window.display();
    }
	return 0;
}