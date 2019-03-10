#include "main.h"

#ifndef FUEL_H
#define FUEL_H


class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z,float r,color_t color);
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
};

#endif // BALL_H
