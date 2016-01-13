#include "ResourceManager.hpp"

ResourceManager* ResourceManager::pInstance = 0;

ResourceManager::ResourceManager() {

    String d = "3";//Res

    //GUI
    if (!t[0].loadFromFile("data/t/0/0.png")) exit(1);
    if (!t[1].loadFromFile("data/t/0/1.png")) exit(1);

    //Car
    if (!t[100].loadFromFile("data/t/1/a.png")) exit(1);

    //Enemy
    if (!t[200].loadFromFile("data/t/1/b.png")) exit(1);

    //Tiles
    if (!t[300].loadFromFile("data/t/" + d + "/000.png")) exit(1);
    if (!t[301].loadFromFile("data/t/" + d + "/001.png")) exit(1);
    if (!t[302].loadFromFile("data/t/" + d + "/002.png")) exit(1);
    if (!t[303].loadFromFile("data/t/" + d + "/003.png")) exit(1);
    if (!t[304].loadFromFile("data/t/" + d + "/004.png")) exit(1);
    if (!t[305].loadFromFile("data/t/" + d + "/005.png")) exit(1);
    if (!t[306].loadFromFile("data/t/" + d + "/006.png")) exit(1);
    if (!t[307].loadFromFile("data/t/" + d + "/007.png")) exit(1);
    if (!t[308].loadFromFile("data/t/" + d + "/008.png")) exit(1);

    if (!f[0].loadFromFile("data/f/DejaVuSansMono.ttf")) exit(1);
}

ResourceManager* ResourceManager::instance() {

    if (pInstance == 0) { pInstance = new ResourceManager; }

    return pInstance;
}

Texture& ResourceManager::getTexture(int id) {

    return t[id];
}

Font& ResourceManager::getFont(int id) {

    return f[id];
}
