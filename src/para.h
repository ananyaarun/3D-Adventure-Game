#include "main.h"

#ifndef PARA_H
#define PARA_H


class Para {
public:
    Para() {}
    Para(float x, float y, float z,float r,color_t color, float speed);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    float speed;
    float radius;
    bounding_box_t getstruct();
private:
    VAO *object;
};

#endif // BALL_H
