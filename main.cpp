#include <SFML/Graphics.hpp>
#include <iostream>
#include <String>
#include <stdlib.h>
#include <time.h>

#include "atoms.hpp"
#include "important.hpp"
#include "typetree.hpp"

using namespace std;

sf::IntRect getTile(int x, int y)
{
    sf::IntRect rect((x-1)*tile_x, (y-1)*tile_y, x+tile_x-1, y+tile_y-1);
    return rect;
}

void loadMap(string map_in, sf::Texture * tileset)
{
    string::iterator iter;
    int ix = 0, iy = 0;
    for(iter=map_in.begin(); iter < map_in.end(); iter++) //Iterate through the map string
    {
        sf::IntRect spr;
        bool dense = 0;
        switch(*iter) //Find what the map is representing and get a path to its icon, as well as its density (This is temporary!)
        {
        case 'S':
            spr = getTile(5,1);
            break;
        case 'W':
            spr = getTile(3,1);
            dense = 1;
            break;
        case 'F':
            spr = getTile(1,1);
            break;
        case 'G':
            spr = getTile(4,1);
            dense = 1;
            break;
        }
        atom obj(tileset, spr, dense);
        obj.x = ix;
        obj.y = iy;
        obj.posFromCoords();
        //obj.loadTexture(tileset);
        if(++ix > 39) //Iterate ix, if it's over 19 then reset it and iterate iy
        {
            ix = 0;
            iy++;
        }
    }
}

int main()
{
    //std::vector<atom> objList;
    tilesetFile = "thing.png";
    sf::Texture * tileset = new sf::Texture;
    tileset->loadFromFile(tilesetFile);
    //L added to start to pad map, hackish! [FIXME]
    string map ="L\
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFW\
WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
    srand(time(NULL));
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "IFR");
    window.setFramerateLimit(10);

    //Initialize the player
    atom Player(tileset, getTile(1,2));
    Player.x = 2;
    Player.y = 2;

    //Create the input handler
    sf::Keyboard KeyIn;

    string::iterator iter;

    loadMap(map, tileset);

    // Start the game loop
    while (window.isOpen())
    {
        // Process window events
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            // Close window/Esc: exit
            if (Event.type == sf::Event::Closed)
                window.close();
        }

        //Process keyboard input
        if(KeyIn.isKeyPressed(sf::Keyboard::Escape))
            window.close();

        else if(KeyIn.isKeyPressed(sf::Keyboard::R))
        {
            objList.clear();
            for(iter=map.begin(); iter < map.end(); iter++)
            {
                switch(rand() % 4)
                {
                case 0:
                    *iter = 'S';
                    break;
                case 1:
                    *iter = 'W';
                    break;
                case 2:
                    *iter = 'F';
                    break;
                case 3:
                    *iter = 'G';
                    break;
                }
            }
            loadMap(map, tileset);
        }
        if(KeyIn.isKeyPressed(sf::Keyboard::Up))
            Player.move(0,-1);
        if(KeyIn.isKeyPressed(sf::Keyboard::Down))
            Player.move(0,1);
        if(KeyIn.isKeyPressed(sf::Keyboard::Left))
            Player.move(-1,0);
        if(KeyIn.isKeyPressed(sf::Keyboard::Right))
            Player.move(1,0);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if((position.x > 0 && position.x <= window_x) && (position.y > 0 && position.y <= window_y))
            {
                static vector<atom>::iterator iter;
                for(iter=objList.begin(); iter != objList.end(); iter++)
                {
                    //cout << position.x + iter->coords.width << "\n";
                    if((position.x >= iter->x*tile_x && position.x <= (iter->x*tile_x)+iter->coords.width)&&(position.y >= iter->y*tile_y && position.y <= (iter->y*tile_y)+iter->coords.height))
                    {
                        atom newtile;
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            newtile.setup(tileset, getTile(5,1), 0);
                        }
                        else //Not left click, so it has to be a rightclick!
                        {
                            newtile.setup(tileset, getTile(1,1), 0);
                        }
                        newtile.x = iter->x;
                        newtile.y = iter->y;
                        objList.erase(iter);
                    }
                }
            }
        }

        // Clear screen
        window.clear();

        // Draw the map
        vector<atom>::iterator iter;
        for(iter=objList.begin(); iter != objList.end(); iter++)
        {
            iter->posFromCoords();
            if(!iter->texrend)
            {
                iter->loadTexture();
                iter->texrend = 1;
            }
            window.draw(iter->spr);
        }

        //Draw the player
        Player.posFromCoords();
        if(!Player.texrend)
        {
            Player.loadTexture();
            Player.texrend=1;
        }
        window.draw(Player.spr);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
