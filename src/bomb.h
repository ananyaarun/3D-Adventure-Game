#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z,float r,color_t color,float rotation, int direction);
    glm::vec3 position;
    float rotation;
    int direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    float radius;

    bounding_box_t getstruct();
private:
    VAO *object;
};

#endif // BALL_H
