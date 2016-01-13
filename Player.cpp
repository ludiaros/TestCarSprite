#include "Player.hpp"

const double Player::PI = 4.0*atan(1);

Player::Player(int type, int x, int y):
    drawable(true),
    alive(true),
    layer(0),
    action(0),
    newact(0),
    mx(0),
    my(0),
    dx(0),
    dy(0),
    lastx(0),
    lasty(0),
    lasta(0),
    vact(0.000),
    vmin(5.000),
    vmax(5.000),
    accu(0.050),
    acct(0.500),
    accb(0.250),
    accd(0.025),
    accn(0.005),
    angle(0),
    turnf(1.5),
    damage(0),
    collision(),
    shadow()
{

    addAnimations();

    setTexture(ResourceManager::instance()->getTexture(type));
    setTextureRect(animations[action].getFrame(0));

    setScale(0.5, 0.5);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height);
    setPosition(x, y);
}

bool Player::update(WindowManager* window) {

    if (animations[action].lock == true) {

        setTextureRect(animations[action].nextFrame());
    }
    else {

        action = newact;
        setTextureRect(animations[action].nextFrame());

        lastx = getPosition().x;
        lasty = getPosition().y;
        lasta = getRotation();

        dx = -vact * cos((90 + angle) * (PI / 180));
        dy = -vact * sin((90 + angle) * (PI / 180));

        if (
            (getPosition().x + dx < SPR_H) || (getPosition().x + dx > MAP_W - SPR_H) ||
            (getPosition().y + dy < SPR_H) || (getPosition().y + dy > MAP_H - SPR_H)
        ) {
            vact = -vact/2;
        }
        else {

            vact = (vact > 0) ? vact - accn : vact + accn;
            if (vact > -accn && vact < accn) vact = 0;

            move(dx, dy);
            setRotation(angle);

            mx = (int) (getPosition().x / TIL_W);
            my = (int) (getPosition().y / TIL_H);

            mx = (mx < 1 ? 1 : mx);
            my = (my < 1 ? 1 : my);

            newact = 0;

            return false;
        }
    }

    return true;
}

void Player::restorePosition() {

    setPosition(lastx, lasty);
    setRotation(lasta);

    mx = (int) (getPosition().x / TIL_W);
    my = (int) (getPosition().y / TIL_H);

    mx = (mx < 1 ? 1 : mx);
    my = (my < 1 ? 1 : my);
}

void Player::turn(int dir) {

    if (vact < 0 || vact > 0) {

        angle += (dir * vact / turnf);

        if (angle > 359) angle -= 360;
        if (angle < 0) angle += 360;
    }
}

void Player::runFW() {

    if (vact < vmax) vact += acct;
}

void Player::walkFW() {

    if (vact < vmax) vact += accu;
}

void Player::walkBW() {

    if (vact > -vmin) {

        if (vact > 0) {
            vact -= accb;
        }
        else {
            vact -= accd;
        }
    }
}

void Player::meleeAttack() {
}

void Player::rangedAttack() {
}

void Player::addAnimations() {

    for (int k=0; k<5; k++) {
        animations.push_back(Animation('b', 5000));//Stop
        for (int i=0; i<2; i++) {
            animations[animations.size()-1].addFrame(IntRect(0, 0, SPR_W, SPR_H));
        }
    }
}
