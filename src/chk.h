#include "main.h"

#ifndef CHK_H
#define CHK_H


class Chk {
public:
    Chk() {}
    Chk(float x, float y, float z,float r,color_t color);
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
};

#endif // BALL_H
