#ifndef ATOMS_HPP_INCLUDED
#define ATOMS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using std::string;

class atom
{
    public:
        bool texrend;
        bool density;
        bool opacity;
        bool visible;
        int x,y;
        sf::IntRect coords;
        sf::Texture * Texture;
        sf::Sprite spr;
        void loadTexture();
        atom(){;} //Blank constructor, CALL SETUP!
        atom(sf::Texture * ts, sf::IntRect coords);
        atom(sf::Texture * ts, sf::IntRect coords, bool dens);
        void setup(sf::Texture * ts, sf::IntRect coords, bool dens);
        bool move(signed int xmove, signed int ymove);
        void posFromCoords();
};

extern std::vector<atom> objList;

#endif
