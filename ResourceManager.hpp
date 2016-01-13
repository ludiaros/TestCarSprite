#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "Config.hpp"

using namespace sf;
using namespace std;

class ResourceManager {

    public:

        //Constructors
        ResourceManager();

        //Methods
        Texture&                getTexture  (int id);
        Font&                   getFont     (int id);

        static ResourceManager* instance    ();

        //Parameters
        map<int, Texture>       t;

        map<int, Font>          f;

    private:

        //Parameters
        static ResourceManager* pInstance;
};


#endif
