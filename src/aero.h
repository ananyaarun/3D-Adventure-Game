#include "main.h"

#ifndef AERO_H
#define AERO_H


class Aero {
public:
    Aero() {}
    Aero(float x, float y, float z,float r,color_t color,float rotation, int direction,int loopin);
    glm::vec3 position;
    glm::mat4 rotate1;
    glm::mat4 rotate2;

    float rotation;
    int direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    float radius;
    int loopin;
    //int loopin = this->loopin;

    bounding_box_t getstruct();
    bounding_box_t getstruct1();

private:
    VAO *object;
};

#endif // BALL_H
