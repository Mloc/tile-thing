#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "important.hpp"
#include "atoms.hpp"
#include <memory>

using namespace std;

std::vector<atom> objList;

void atom::loadTexture()
{
    this->spr.setTexture(*(this->Texture));
    this->spr.setTextureRect(this->coords);
}

atom::atom(sf::Texture * ts, sf::IntRect coords)
{
    this->setup(ts, coords, 0);
}

atom::atom(sf::Texture * ts, sf::IntRect coords, bool dens)
{
    this->setup(ts, coords, dens);
}

void atom::setup(sf::Texture * ts, sf::IntRect coords, bool dens)
{
    this->coords = coords;
    this->texrend = 0;
    this->density = dens;
    this->Texture = ts;
    objList.push_back(*this);
}

bool atom::move(signed int xmove, signed int ymove)
{
    static vector<atom>::iterator iter;
    for(iter=objList.begin(); iter != objList.end(); iter++)
    {
        if((iter->x == (this->x+xmove)) && (iter->y == this->y+ymove))
        {
            if(iter->density)
            {
                return 0;
            }
        }
    }
    this -> x += xmove;
    this -> y += ymove;
    this -> posFromCoords();
    return 1;
}

void atom::posFromCoords()
{
    this->spr.setPosition((this->x)*tile_x, (this->y)*tile_y);
}
