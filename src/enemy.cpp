#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y,float z, float r, color_t color) 
{
     this->position = glm::vec3(x, y, z);
    this->radius=r;
    this->speed=speed;
    //this->rotation = rotation;
    const double PI=3.14159265358979324;
    
    GLfloat g_vertex_buffer_data[100000];
    int j=0;
    double xcor[360];
    double ycor[360];
    for (int i = 0; i < 360; i++)
    {
    
        xcor[i] = 1.8*r * cos(2.0*PI*i/360);
        ycor[i] = 1.8*r * sin(2.0*PI*i/360);
        
    }

    for(int i=0;i<360;i++)
    {
        int ht = rand()%10+3;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.2f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        

    }

      

    this->object = create3DObject(GL_TRIANGLES, j, g_vertex_buffer_data, color, GL_FILL);

}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Enemy::getstruct(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.z = this->position.z;
    t1.width = 2.5;
    t1.height = 2.5;
    t1.depth = 1.5;
    return t1;
}

bounding_box_t Enemy::getstruct1(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.z = this->position.z;
    t1.width = 7;
    t1.height = 7;
    t1.depth = 7;
    return t1;
}


