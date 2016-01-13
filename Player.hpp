#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>

#include "Config.hpp"
#include "ResourceManager.hpp"
#include "WindowManager.hpp"
#include "Animation.hpp"

using namespace sf;
using namespace std;

class Player : public Sprite {

    public:

        //Constructors
        Player(int type, int x, int y);

        //Methods
        void                turn            (int dir);
        void                runFW           ();
        void                walkFW          ();
        void                walkBW          ();
        void                meleeAttack     ();
        void                rangedAttack    ();
        void                restorePosition ();
        void                addAnimations   ();

        bool                update          (WindowManager* window);

        int                 getX            ()              { return (int) getPosition().x; };
        int                 getY            ()              { return (int) getPosition().y; };

        float               getSpeed        ()              { return (int) (vact*10) / 10.f; };
        float               getTime         ();

        //Parameters
        bool                drawable;
        bool                alive;

        int                 layer;
        int                 action;
        int                 newact;
        int                 mx;
        int                 my;

        float               dx;                             // Delta de desplazamiento en el eje x
        float               dy;                             // Delta de desplazamiento en el eje y
        float               lastx;
        float               lasty;
        float               lasta;
        float               vact;                           // Velocidad actual
        float               vmin;                           // Velocidad minima
        float               vmax;                           // Velocidad maxima con la aceleracion normal
        float               accu;                           // Tasa de aceleracion
        float               acct;                           // Tasa de aceleracion por nitro
        float               accb;                           // Tasa de desaceleracion por frenado
        float               accd;                           // Tasa de desaceleracion por reversa
        float               accn;                           // Tasa de desaceleracion por friccion
        float               angle;                          // Angulo de movimiento
        float               turnf;                          // Tasa de giro
        float               damage;                         // Daño recibido?

        Sprite              collision;
        Sprite              shadow;

        vector<Animation>   animations;

    private:

        //Parameters
        static const double PI;
};

#endif
