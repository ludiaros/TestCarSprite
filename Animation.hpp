#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Config.hpp"

using namespace sf;
using namespace std;

class Animation {

    public:

        //Constructors
        Animation(char type, int delay);

        //Methods
        void            addFrame(IntRect frame);

        IntRect         getFrame(int i);
        IntRect         currentFrame();
        IntRect         nextFrame();


        //Parameters
        char            type;

        bool            lock;

        int             delay;
        int             current;
        int             inc;

        Clock           time;

        vector<IntRect> frames;
};

#endif
