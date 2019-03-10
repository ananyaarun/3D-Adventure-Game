#include "comp.h"
#include "main.h"
Comp::Comp(float x, float y,float z, float rotation, color_t color,color_t color1, color_t color2) 
{
     this->position = glm::vec3(x, y, z);
    this->rotation=rotation;
    this->speed=speed;
     const double PI=3.14159265358979324;
    
    GLfloat g_vertex_buffer_data[100000];
    int j=0;
    double xcor[360];
    double ycor[360];
    for (int i = 0; i < 360; i++)
    {
    
        xcor[i] = 0.4 * cos(2.0*PI*i/360);
        ycor[i] = 0.4 * sin(2.0*PI*i/360);
        
    }
    
    for(int i=0;i<360;i++)
    {
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        
    };

    static const GLfloat vertex_buffer_data1[] = {
       0.0f,0.01f,0.3f,
       0.1f,0.01f,0.0f,
       -0.1f,0.01f,0.0f


    };

     static const GLfloat vertex_buffer_data2[] = {
    
       0.0f,0.01f,-0.3f,
       0.1f,0.01f,0.0f,
       -0.1f,0.01f,0.0f
    };

      
    this->object = create3DObject(GL_TRIANGLES, j, g_vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, color2, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, color1, GL_FILL);


}

void Comp::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= ( translate * rotate);
    glm::mat4 MVP = VP*Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    
}

void Comp::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}


