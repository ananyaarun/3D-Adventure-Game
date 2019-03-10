#include "main.h"

#ifndef COMP_H
#define COMP_H


class Comp {
public:
    Comp() {}
    Comp(float x, float y, float z,float r,color_t color, color_t color1, color_t color2);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    float radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;

};

#endif // BALL_H
