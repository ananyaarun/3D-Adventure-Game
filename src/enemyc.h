#include "main.h"

#ifndef ENEMYC_H
#define ENEMYC_H


class Enemyc {
public:
    Enemyc() {}
    Enemyc(float x, float y, float z,float r,color_t color, color_t color1);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    float radius;
    bounding_box_t getstruct();
private:
    VAO *object;
    VAO *object1;

};

#endif // BALL_H
