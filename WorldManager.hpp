#ifndef WORLDMANAGER_HPP
#define WORLDMANAGER_HPP

#include "Config.hpp"
#include "WindowManager.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

#include "Collision.h"

using namespace sf;
using namespace std;

class WorldManager {

    public:

        //Constructors
        WorldManager();

        //Methods
        static WorldManager*        instance            ();

        void                        events              ();
        void                        changePerspective   ();

        void                        addPlayer           (int type);
        void                        addEnemy            (int type);
        void                        evalCollisions      (WindowManager* window);
        void                        update              (WindowManager* window, int layer);
        void                        draw                (WindowManager* window, int layer);
        void                        notifyCollision     (int layer, int i);

        //Parameters
        map< int, map<int, Tile> >  tiles;
        map< int, vector<int> >     collision;

        vector<Player>              players;
        vector<Enemy>               enemies;

        int                         m;
        int                         n_players;
        int                         n_enemies;

    private:

        //Parameters
        static WorldManager*        pInstance;
};

#endif
