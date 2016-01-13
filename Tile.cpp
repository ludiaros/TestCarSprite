#include "Tile.hpp"

Tile::Tile() {}

Tile::Tile(int id, int x, int y):
    drawable(true),
    color(),
    tile_id(id)
{
    Texture& t = ResourceManager::instance()->getTexture(id);

    setTexture(t);//Load from ResourceManager

    color = getColor();

    setPosition(x, y);

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

    setRotation((rand()%4)*90);
}

void Tile::update(View view) {

    /*drawable = true;

    if (
        getPosition().x < view.getCenter().x - view.getSize().x ||
        getPosition().x > view.getCenter().x + view.getSize().x ||
        getPosition().y < view.getCenter().y - view.getSize().y ||
        getPosition().y > view.getCenter().y + view.getSize().y
    ) {
        drawable = false;
    }
    else {*/
        setColor(color);
    /*}*/
}
