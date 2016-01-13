#include "EventManager.hpp"

EventManager* EventManager::pInstance = 0;

EventManager::EventManager() {
}

EventManager* EventManager::instance() {

    if (pInstance == 0) { pInstance = new EventManager; }

    return pInstance;
}

void EventManager::update(WorldManager* world) {

    if (Keyboard::isKeyPressed(Keyboard::Add)) { WindowManager::instance()->setZoom(0.9); }

    if (Keyboard::isKeyPressed(Keyboard::Subtract)) { WindowManager::instance()->setZoom(1.1); }

    if (Keyboard::isKeyPressed(Keyboard::Numpad0)) { WindowManager::instance()->resetZoom(); }

    Event event;

    while (WindowManager::instance()->pollEvent(event)) {

        if (event.type == Event::Closed) {

            WindowManager::instance()->close();
        }

        if (event.type == Event::MouseWheelMoved) {

            WindowManager::instance()->setZoom(1 - (float) event.mouseWheel.delta / 20);
        }

        if (event.type == Event::KeyPressed) {

            switch (event.key.code) {

                case Keyboard::Space:
                    world->changePerspective();
                break;

                case Keyboard::F4:
                    if (Keyboard::isKeyPressed(Keyboard::LAlt)) WindowManager::instance()->close();
                break;

                case Keyboard::F11:
                    WindowManager::instance()->toggleFullScreen();
                break;

                case Keyboard::Escape:
                    WindowManager::instance()->paused = !WindowManager::instance()->paused;
                break;

                case Keyboard::I:
                    WindowManager::instance()->show_info = !WindowManager::instance()->show_info;
                break;

                case Keyboard::F:
                    WindowManager::instance()->show_fps = !WindowManager::instance()->show_fps;
                break;
            }
        }
    }
}
