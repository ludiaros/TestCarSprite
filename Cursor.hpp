#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <cmath>

#include "Config.hpp"

#include "WindowManager.hpp"
#include "ResourceManager.hpp"

using namespace sf;
using namespace std;

class Cursor : public Sprite {

    public:

        //Constructors
        Cursor();

        //Methods
        static Cursor*  instance    ();
        void            update      (WindowManager* window);

        //Parameters
        bool            drawable;

        Color           color;

        int             mod;

    private:

        //Parameters
        static Cursor*  pInstance;
};

#endif
