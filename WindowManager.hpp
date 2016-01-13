#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "Config.hpp"

using namespace sf;
using namespace std;

class WindowManager : public RenderWindow {

    public:

        //Constructors
        WindowManager();

        //Methods
        static WindowManager*   instance            ();

        void                    setDefaultView      ();
        void                    toggleFullScreen    ();
        void                    resetZoom           ();

        void                    setZoom             (float z);
        void                    updateView          (Vector2f center, float angle);

        //Parameters
        int                     style;

        bool                    show_info;
        bool                    show_fps;
        bool                    fullscr;
        bool                    paused;

        float                   zoom;
        float                   px;
        float                   py;

        VideoMode               video;

        String                  tfps;
        String                  info;

        View                    view;

        Text                    text;

        Clock                   fps;

    private:

        //Parameters
        static WindowManager*   pInstance;
};

#endif
