#include "WorldManager.hpp"

WorldManager* WorldManager::pInstance = 0;

WorldManager::WorldManager():
    m(0),
    n_players(2),
    n_enemies(9)
{

    srand(time(NULL));

    ///////////////////////////////////////////////////////////////////////////////

    for (int row=0; row<SUB; row++) {

        for (int col=0; col<SUB; col++) {

            int t = 306;
            tiles[0][row*SUB+col] = Tile(t, col*TIL_W, row*TIL_H);
            tiles[1][row*SUB+col] = Tile(300, col*TIL_W, row*TIL_H);
            collision[row*SUB+col].push_back(0);//Type 0 - trespassable terrain
            collision[row*SUB+col].push_back(0);//Collision layer
        }
    }

    ///////////////////////////////////////////////////////////////////////////////

    players.push_back(Player(100, SCR_W/2, SCR_H/2));
    n_players--;

    while (n_players > 0) {

        players.push_back(Player(100, rand()%SCR_W, rand()%SCR_H));
        n_players--;
    }

    ///////////////////////////////////////////////////////////////////////////////

    while (n_enemies > 0) {

        enemies.push_back(Enemy(200, rand()%MAP_W/2, rand()%MAP_H/2));
        n_enemies--;
    }
}

WorldManager* WorldManager::instance() {

    if (pInstance == 0) { pInstance = new WorldManager; }

    return pInstance;
}

void WorldManager::update(WindowManager* window, int layer) {

    int mx = (int) (window->px / TIL_W);
    int my = (int) (window->py / TIL_H);

    int qx = 10;
    int qy = 10;

    mx = (mx < qx ? qx : mx);
    my = (my < qy ? qy : my);

    for (int row=my-qy; row<=my+qy+1; row++) {

        for (int col=mx-qx; col<=mx+qx+1; col++) {

            if (tiles[layer][row*SUB+col].tile_id == 300) {
            }
            else {
                tiles[layer][row*SUB+col].update(window->view);
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////

    for (unsigned int i=0; i<players.size(); ++i) {
        if (i!=m) {
            //players[i].AI();
        }
        players[i].update(window);
    }

    //////////////////////////////////////////////////////////////////////////

    for (unsigned int i=0; i<enemies.size(); ++i) {
        //if (i!=m) {
            //enemies[i].AI();
        //}
        enemies[i].update(window);
    }
}

void WorldManager::draw(WindowManager* window, int layer) {

    int mx = (int) (window->px / TIL_W);
    int my = (int) (window->py / TIL_H);

    int qx = 10;
    int qy = 10;

    mx = (mx < qx ? qx : mx);
    my = (my < qy ? qy : my);

    for (int row=my-qy; row<=my+qy; row++) {

        for (int col=mx-qx; col<=mx+qx; col++) {

            if (tiles[layer][row*SUB+col].tile_id == 300) {
            }
            else {
                window->draw(tiles[layer][row*SUB+col]);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    for (unsigned int i=0; i<players.size(); ++i) {

        if (players[i].layer == layer) {
            window->draw(players[i]);
        }
    }

    ///////////////////////////////////////////////////////////////////////////

    for (unsigned int i=0; i<enemies.size(); ++i) {

        if (enemies[i].layer == layer) {
            window->draw(enemies[i].shadow);
            window->draw(enemies[i]);
        }
    }
}

void WorldManager::notifyCollision(int layer, int i) {

    //tiles[layer][i].setColor(Color(255, 255, 255, 200));
}

void WorldManager::changePerspective() {

    m++;
    if (m == players.size()) m = 0;
}

void WorldManager::addPlayer(int type) {

    players.push_back(Player(type,rand()%SCR_W, rand()%SCR_H));
}

void WorldManager::addEnemy(int type) {

    enemies.push_back(Enemy(type,rand()%SCR_W, rand()%SCR_H));
}

void WorldManager::evalCollisions(WindowManager* window) {

    int layer;

    for (unsigned int i=0; i<players.size(); ++i) {

        for (int row=players[i].my-1; row<=players[i].my+1; row++) {

            for (int col=players[i].mx-1; col<=players[i].mx+1; col++) {

                switch (collision[row*SUB+col][0]) {

                    case 0:
                    break;

                    case 1:
                        if (Collision::BoundingBoxTest(players[i], tiles[layer][row*SUB+col])) {
                            players[i].restorePosition();
                        }
                    break;

                    case 2:
                        layer = collision[row*SUB+col][1];
                        if (Collision::BoundingBoxTest(players[i], tiles[layer][row*SUB+col])) {

                            if (Collision::PixelPerfectTest(players[i], tiles[layer][row*SUB+col], 64)) {

                                notifyCollision(layer, row*SUB+col);

                                players[i].restorePosition();
                                //players[i].damage += 0.1;
                            }
                        }
                    break;

                    default:
                    break;
                }

                if (collision[row*SUB+col][1] == 300) {
                    players[i].restorePosition();
                }
            }
        }

        for (int j=i+1; j<players.size(); j++) {

            if (Collision::BoundingBoxTest(players[i], players[j])) {

                if (Collision::PixelPerfectTest(players[i], players[j], 64)) {

                    players[i].restorePosition();
                    players[i].vact = -players[i].vact/2;
                    //players[i].damage += 0.1;
                }
            }
        }

        for (int j=0; j<enemies.size(); j++) {

            if (Collision::BoundingBoxTest(players[i], enemies[j])) {

                if (Collision::PixelPerfectTest(players[i], enemies[j], 64)) {

                    players[i].restorePosition();
                    players[i].vact = -players[i].vact/2;
                    //players[i].damage += 0.1;
                }
            }
        }
    }

    for (unsigned int i=0; i<enemies.size(); ++i) {

        for (int j=enemies[i].mx-1; j<enemies[i].mx+2; j++) {

            for (int k=enemies[i].my-1; k<enemies[i].my+2; k++) {

                for (int l=0; l<tiles.size(); l++) {

                    if (
                        tiles[l][j*SUB+k].tile_id == 300 ||
                        tiles[l][j*SUB+k].tile_id == 306
                    ) {

                        if (Collision::BoundingBoxTest(enemies[i], tiles[l][j*SUB+k])) {

                            if (Collision::PixelPerfectTest(enemies[i], tiles[l][j*SUB+k], 64)) {

                                notifyCollision(l, j*SUB+k);

                                enemies[i].restorePosition();
                                enemies[i].angle = enemies[i].angle + (180 + rand()%180);
                                //enemies[i].damage += 0.1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void WorldManager::events() {

    if (Mouse::isButtonPressed(Mouse::Left)) {

        players[m].meleeAttack();
    }

    if (Mouse::isButtonPressed(Mouse::Right)) {

        players[m].rangedAttack();
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {

        if (Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) {
            players[m].runFW();
        }
        else {
            players[m].walkFW();
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {

       players[m].walkBW();
    }

    if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {

        if (Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) {
            players[m].turn(-2);
        }
        else {
            players[m].turn(-1);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {

        if (Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) {
            players[m].turn(2);
        }
        else {
            players[m].turn(1);
        }
    }
}
