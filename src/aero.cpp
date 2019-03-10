#include "aero.h"
#include "main.h"
Aero::Aero(float x, float y,float z, float r, color_t color,float rotation, int direction, int loopin) 
{
     this->position = glm::vec3(x, y, z);
     glm::mat4 rotate1 = glm::mat4(1.0f);
     glm::mat4 rotate2 = glm::mat4(1.0f);

    this->radius=r;
    this->speed=speed;
    this->rotation = rotation;
    this->direction = direction;
    this->loopin = loopin;
    const double PI=3.14159265358979324;
    
    GLfloat g_vertex_buffer_data[(3*100000)+18];
    int j=0;
    double xcor[360];
    double ycor[360];
    for (int i = 0; i < 360; i++)
    {
    
        xcor[i] = r * cos(2.0*PI*i/360);
        ycor[i] = r * sin(2.0*PI*i/360);
        
    }
    for(int i=0;i<360;i++)
    {
        

        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=1.8f;
        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        g_vertex_buffer_data[j++]=0.0f;

        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        g_vertex_buffer_data[j++]=1.8f;
        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=1.8f;
        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        g_vertex_buffer_data[j++]=0.0f;



        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=-0.5f;
        g_vertex_buffer_data[j++]=xcor[i%360];
        g_vertex_buffer_data[j++]=ycor[i%360];
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=xcor[(i+1)%360];
        g_vertex_buffer_data[j++]=ycor[(i+1)%360];
        g_vertex_buffer_data[j++]=0.0f;

    }

        g_vertex_buffer_data[j++]=0.3f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=1.8f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.5f;
        g_vertex_buffer_data[j++]=0.3f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=1.0f;

        g_vertex_buffer_data[j++]=-0.3f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=-1.8f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=0.5f;
        g_vertex_buffer_data[j++]=-0.3f;
        g_vertex_buffer_data[j++]=0.0f;
        g_vertex_buffer_data[j++]=1.0f;

    this->object = create3DObject(GL_TRIANGLES, j, g_vertex_buffer_data, color, GL_FILL);

}
//int a,b,c;
 int a=1;
 int b=0;
 int c=0;

void Aero::draw(glm::mat4 VP) {
if(loopin==0)
{
    if(this->direction == 1)
    {
        a=0;
        b=1;
        c=0;
    }
    
    else if(this->direction == 2)
    {

        a=0;
        b=0;
        c=1;
    }
      else
      {
          a=1;
          b=0;
          c=0;

      }
      
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(a,b,c));
    
    rotate1 *= rotate;
   // if(direction==2 || direction ==1)
   // if(direction == 2){
        
    Matrices.model *= (translate * rotate1);
    //else
    //Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    this->rotation = 0;
    this->direction = 0;
//}
 //else{
   // Matrices.model *= (translate * rotate);
    //else
    //Matrices.model *= (translate * rotate);
   // glm::mat4 MVP = VP * Matrices.model;
    //glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object);

    //this->rotation = 0;
    //this->direction = 0;
//}
}
if(loopin ==1)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (45.0f * M_PI / 180.0f), glm::vec3(1,0,0));
    
    //rotate1 *= rotate;
   // if(direction==2 || direction ==1)
   // if(direction == 2){
        
    Matrices.model *= (translate * rotate);
    //else
    //Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

   // this->rotation = 0;
    //this->direction = 0;

}

if(loopin ==2)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (-45.0f * M_PI / 180.0f), glm::vec3(1,0,0));
    
    //rotate1 *= rotate;
   // if(direction==2 || direction ==1)
   // if(direction == 2){
        
    Matrices.model *= (translate * rotate);
    //else
    //Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

   // this->rotation = 0;
    //this->direction = 0;

}

if(loopin ==3)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (170.0f * M_PI / 180.0f), glm::vec3(1,0,0));
    
    //rotate1 *= rotate;
   // if(direction==2 || direction ==1)
   // if(direction == 2){
        
    Matrices.model *= (translate * rotate);
    //else
    //Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

   // this->rotation = 0;
    //this->direction = 0;

}

}

void Aero::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}


bounding_box_t Aero::getstruct1(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.z = this->position.z;
    t1.width = 0.9;
    t1.height = 20.9;
    t1.depth = 2.3;
    return t1;

}

bounding_box_t Aero::getstruct(){
    bounding_box_t t1;
    t1.x= this->position.x;
    t1.y= this->position.y;
    t1.z = this->position.z;
    t1.width = 0.9;
    t1.height = 0.9;
    t1.depth = 2.3;
    return t1;
}