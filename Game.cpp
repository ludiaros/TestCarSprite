#include <SFML/Window.hpp>

#include <sstream>
#include <iostream>

#include "ResourceManager.hpp"
#include "WindowManager.hpp"
#include "EventManager.hpp"
#include "WorldManager.hpp"

#include "Cursor.hpp"

ResourceManager*    resources   = ResourceManager::instance();
WindowManager*      window      = WindowManager::instance();
EventManager*       event       = EventManager::instance();
WorldManager*       world       = WorldManager::instance();

Cursor              cursr;

int main(int argc, char **argv) {

    int min = 0;

    while (window->isOpen()) {

        window->fps.restart();

        // Event -------------------------------------------------------
        event->update(world);
        world->events();

        // Logic -------------------------------------------------------
        if (!window->paused) {

            world->update(window, 0);
            world->evalCollisions(window);
            world->update(window, 1);

        }

        // Render ------------------------------------------------------
        window->clear();

        window->updateView(world->players[world->m].getPosition(), 0/*world->players[world->m].getRotation()*/);

        world->draw(window, 0);
        world->draw(window, 1);

        window->updateView(world->players[world->m].getPosition(), 0);
        cursr.update(window);
        window->draw(cursr);

        window->setDefaultView();

        if (window->show_fps) {
            window->text = Text("FPS: " + window->tfps, ResourceManager::instance()->getFont(0), 16);
            window->text.setStyle(Text::Bold);
            window->text.setPosition(5, 5);
            window->draw(window->text);
        }

        window->display();

        // Other--------------------------------------------------------

        stringstream txt1;
        txt1 << 1000/window->fps.getElapsedTime().asMilliseconds() << flush;
        window->tfps = txt1.str();
    }
    return EXIT_SUCCESS;
}
