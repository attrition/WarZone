#include <SFML/Graphics.hpp>

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "WarZone!");

    // map params
    int width = 40;
    int height = 27;
    int scale = 2;
    int tileSize = 16;
    int menuRows = 3;
    int yOffset = tileSize * menuRows;
    int tileScaled = tileSize * scale;
    int yOffsetScaled = yOffset * scale;

    // grass tile
    sf::Texture grassTex;
    grassTex.loadFromFile("assets/textures/grass.png");
    sf::Image grassImg = grassTex.copyToImage();

    // selection graphic
    sf::Texture selectionTex;
    selectionTex.loadFromFile("assets/textures/selection.png");
    sf::Sprite selection(selectionTex);
    selection.scale(scale, scale);

    // map graphic
    sf::Texture mapTex;
    mapTex.create(width * tileSize, height * tileSize + yOffset);
    
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            mapTex.update(grassImg, x * tileSize, y * tileSize + yOffset);

    sf::Sprite map(mapTex);
    map.scale(scale, scale);
    
    // mouse details
    sf::Vector2i mouse(sf::Mouse::getPosition());
    int gridX = 0; // mouse coords on map tile grid
    int gridY = 0;

    // main loop
    while (window.isOpen())
    {
        // event handling
        {
            sf::Event event;
            window.pollEvent(event); // may drop events, need proper handling

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }

            if (event.type == sf::Event::MouseMoved)
                mouse = sf::Mouse::getPosition(window);
        }

        // update func
        {
            mouse = sf::Mouse::getPosition(window);
            gridX = (mouse.x / tileScaled) * tileScaled;
            gridY = (mouse.y / tileScaled) * tileScaled;
        
            selection.setPosition(gridX, gridY);
        }
        
        // render func
        {
            window.clear();
            window.draw(map);

            if (gridY >= yOffsetScaled)
                window.draw(selection);
                
            window.display();
        }
    }

    return 0;
}