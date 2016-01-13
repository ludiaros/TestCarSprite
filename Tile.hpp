#ifndef TILE_HPP
#define TILE_HPP

#include <cmath>

#include "Config.hpp"
#include "ResourceManager.hpp"

using namespace sf;
using namespace std;

class Tile : public Sprite {

    public:

        //Constructors
        Tile();
        Tile(int id, int x, int y);

        //Methods
        void    update      (View view);

        //Parameters
        bool    drawable;

        Color   color;

        int     tile_id;
};

#endif
