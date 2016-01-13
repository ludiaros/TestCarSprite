#include "Animation.hpp"

Animation::Animation(char type, int delay):
    type(type),
    lock(false),
    delay(delay),
    current(0),
    time(),
    inc(1)
{

    //animations.push_back(IntRect(0, 384, SPR_W, SPR_H));
}

void Animation::addFrame(IntRect frame) {

    frames.push_back(frame);
}

IntRect Animation::getFrame(int i) {

    return frames[i];
}

IntRect Animation::currentFrame() {

    return frames[current];
}

IntRect Animation::nextFrame() {

    if (time.getElapsedTime().asMilliseconds() > delay) {

        switch (type) {

            case 'b'://back-forward
                inc = (current + inc < frames.size() ? inc : -inc);
                inc = (current + inc >= 0 ? inc : -inc);
                current = current + inc;
            break;

            case 'l'://loop
                current = (current + 1 < frames.size() ? current + 1 : 0);
            break;

            case 'o'://once (lock action)
                lock = true;
                if (current + 1 < frames.size()) {
                    current = current + 1;
                }
                else {
                    lock = false;
                    current = 0;
                }
            break;

            case 'k'://once + back-forward (lock action)
                lock = true;
                if (current + inc < frames.size()) {
                    current = current + inc;
                    if (current == 0) {
                        lock = false;
                        current = 0;
                        inc = 1;
                    }
                }
                else {
                    inc = -inc;
                }

            break;
        }

        time.restart();
    }
    return frames[current];
}
