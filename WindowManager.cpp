#include "WindowManager.hpp"

WindowManager* WindowManager::pInstance = 0;

WindowManager::WindowManager():
    show_info(true),
    show_fps(true),
    fullscr(false),
    paused(false),
    zoom(1),
    px(0),
    py(0)
{

    toggleFullScreen();

    view.reset(FloatRect(MAP_W/2, MAP_H/2, video.width, video.height));
    setZoom(ZOOM);
}

WindowManager* WindowManager::instance() {

    if (pInstance == 0) { pInstance = new WindowManager; }

    return pInstance;
}

void WindowManager::setDefaultView() {

    setView(getDefaultView());
}

void WindowManager::toggleFullScreen() {

    if (fullscr) {

        video.width = video.getDesktopMode().width;
        video.height = video.getDesktopMode().height;
        style = Style::Fullscreen;
    }
    else {

        video.width = SCR_W;
        video.height = SCR_H;
        style = Style::Default;
    }

    create(video, "Ivernia Legend", style);

    setVerticalSyncEnabled(true);
    setMouseCursorVisible(false);
    setKeyRepeatEnabled(false);

    fullscr = !fullscr;
}

void WindowManager::resetZoom() {

    view.zoom(ZOOM/ zoom);
    zoom = ZOOM;
}

void WindowManager::setZoom(float z) {

    if (z * zoom >= 0.25 && z * zoom <= 4) {
        zoom = z * zoom;
        view.zoom(z);
    }
}

void WindowManager::updateView(Vector2f center, float angle) {

    px = center.x;
    py = center.y;

    view.setCenter(center);
    view.setRotation(angle);

    setView(view);
}
