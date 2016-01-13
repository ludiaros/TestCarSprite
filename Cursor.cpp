#include "Cursor.hpp"

Cursor* Cursor::pInstance = 0;

Cursor::Cursor():
    drawable(true),
    color(),
    mod(2)
{
    setTexture(ResourceManager::instance()->getTexture(1));//Load from ResourceManager

    setScale(0.25, 0.25);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    setPosition(0, 0);

    color = getColor();
    setColor(Color(255, 255, 255, 255));
}

Cursor* Cursor::instance() {

    if (pInstance == 0) { pInstance = new Cursor; }

    return pInstance;
}

void Cursor::update(WindowManager* window) {

    int x = Mouse::getPosition(*window).x + window->px - SCR_W/2;
    int y = Mouse::getPosition(*window).y + window->py - SCR_H/2;

    x = (x > 0 ? x : 0);
    y = (y > 0 ? y : 0);

    if (x >= 0 && y >= 0) {

        setPosition(x, y);

    }
    if (getColor().a <= 100) {
        setColor(Color(getColor().r-mod, getColor().g, getColor().b, 105));
        mod = -mod;
    }
    if (getColor().a >= 255) {
        setColor(Color(getColor().r-mod, getColor().g, getColor().b, 250));
        mod = -mod;
    }
    setColor(Color(getColor().r-mod, getColor().g, getColor().b, getColor().a-mod));
}
