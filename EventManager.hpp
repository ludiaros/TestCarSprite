#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Config.hpp"

#include "WindowManager.hpp"
#include "WorldManager.hpp"

using namespace sf;
using namespace std;

class EventManager {

    public:

        //Constructors
        EventManager();

        //Methods
        static EventManager*    instance    ();

        void                    update      (WorldManager* world);

        //Parameters
        //...

    private:

        //Parameters
        static EventManager*    pInstance;
};

#endif
