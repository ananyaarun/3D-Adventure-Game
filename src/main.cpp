#include "main.h"
#include "timer.h"
#include "aero.h"
#include "sea.h"
#include "land.h"
#include "hill.h"
#include "ring.h"
#include "enemy.h"
#include "para.h"
#include "missile.h"
#include "bomb.h"
#include "comp.h"
#include "score.h"
#include "chk.h"
#include "enemyc.h"
#include "gun.h"
#include "fuel.h"
#include "flag.h"
#include "circ.h"
#include "speed.h"
#include "tar.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Tar tar;
Sea sea;
Land land;
Aero aero;
Hill hill[80];
Ring ring[10];
Enemy enemy[88];
Para para[60];
Missile missile;
Bomb bomb;
Comp comp;
Circ circ;
Flag flag1;
Fuel fuelup[10];
Score s1[2];
Score s2[2];
Chk cp1,cp2,cp3,cp4;
Enemyc enemyc[20];
Gun gun[20];
Speed spe;

int ht=0;
int guncp1[5]={0};
int guncp2[5]={0};
int guncp3[5]={0};
int guncp4[5]={0};
int fuel=99;
int fu=99;
float acc = 0.001;
int nm =0;
int view=2;
int tarit = 0;

float eye_x,eye_y,eye_z;
float target_x,target_y,target_z;
float screen_zoom = 105, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float cr=0;
float cr1=0;

int chk =0;
int chk1=0;
int cp=1;
int height1,height2;
int height3,height4;
int pchk[60]={0};
int gu[20]={0};
int ringo[10]={0};

extern float heliy;
float angle1=45;
float angle2=45;
extern bool cannon_keyboard_input, drag_pan;
extern double drag_oldx, drag_oldy;
extern double r;

int score =0;
int health = 7;
int level = 1;
float spea=0;

Timer t60(1.0 / 60);
Timer tfu(5.0);
Timer tsco(1.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
  //  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    
    //plane view
    if(view==0)
        { 
     	    eye_x=  (0*(sin((M_PI/180)*cr)))+aero.position.x;
     	    eye_y = 3+aero.position.y;
     	    eye_z = (1.55*(cos((M_PI/180)*cr)))+aero.position.z;

     	    target_x = (0*(sin((M_PI/180)*cr)))+aero.position.x;
     	    target_y = 3+aero.position.y; 
     	    target_z = (20*(cos((M_PI/180)*cr)))+aero.position.z;
        }
    
    //top view
    if(view==1)
    	{  
    		eye_x= (0*(sin((M_PI/180)*cr)))+aero.position.x;
     	    eye_y = 20+aero.position.y;
     	    eye_z = (0.0001*(cos((M_PI/180)*cr)))+aero.position.z;

     	    target_x = (0*(sin((M_PI/180)*cr)))+aero.position.x;
     	    target_y = 0+aero.position.y; 
     	    target_z = (0*(cos((M_PI/180)*cr)))+aero.position.z;

     	    
    	     
    	}

    //tower view 
    if(view==2)
        { 
     	    eye_x=  (10*(sin((M_PI/180)*cr)))+aero.position.x+5;
     	    eye_y = 10+aero.position.y;
     	    eye_z = (10*(cos((M_PI/180)*cr)))+aero.position.z;

     	    target_x = (0*(sin((M_PI/180)*cr)))+aero.position.x;
     	    target_y = 0+aero.position.y; 
     	    target_z = (0*(cos((M_PI/180)*cr)))+aero.position.z;


        }
    
    //follow cam view
    if(view==3)
    	{  
    		
    	    eye_x=  (10*(sin((M_PI/180)*cr)))+aero.position.x;
     	    eye_y = 3.5+aero.position.y;
     	    eye_z = (10*(cos((M_PI/180)*cr)))+aero.position.z;

     	    target_x = (0*(sin((M_PI/180)*cr)))+aero.position.x;
     	    target_y = 0+aero.position.y; 
     	    target_z = (0*(cos((M_PI/180)*cr)))+aero.position.z;

    	}

    // helicopter view
    if(view==4)
    	{  

    		eye_x= r*sin(camera_rotation_angle);
     	    eye_y = heliy;
     	    eye_z = r*cos(camera_rotation_angle);

     	    target_x = 0+aero.position.x;
     	    target_y = 0+aero.position.y; 
     	    target_z = 0+aero.position.z;
    	     
    	}

    glm::vec3 eye (eye_x,eye_y,eye_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x,target_y,target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0,1,0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view1 = glm::lookAt(glm::vec3(0, 3, 0.0001), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VP1 = Matrices.projection * Matrices.view1;
    
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    land.draw(VP);
    
    sea.draw(VP);
    
    //if(tarit==1)
    //{
    //	tar.draw(VP);
    //	tarit=0;
    //}

    if(cp==5)
        flag1.draw(VP);

    for(int i =0;i<80;i++)
    	hill[i].draw(VP);
    
    for(int i =0;i<88;i++)
    	enemy[i].draw(VP);

    for(int i =0;i<20;i++)
    	enemyc[i].draw(VP);

    for(int i =0;i<5;i++)
        if(gu[i]==1 && guncp1[i]==0)
    	    gun[i].draw(VP);
    
    for(int i =5;i<10;i++)
        if(gu[i]==1 && guncp2[i]==0)
    	    gun[i].draw(VP);
    
    for(int i =10;i<15;i++)
        if(gu[i]==1 && guncp3[i]==0)
    	    gun[i].draw(VP);
    
    for(int i =15;i<20;i++)
        if(gu[i]==1 && guncp4[i]==0)
    	    gun[i].draw(VP);
    
    aero.draw(VP);
    
    for(int i=0;i<10;i++)
    	ring[i].draw(VP);
    
    for(int i=0;i<60;i++)
    	para[i].draw(VP);
    
    if(chk==1)
        missile.draw(VP);

    if(chk1==1)
    	bomb.draw(VP);

    //comp.draw(VP1);

    circ.draw(VP1);

    comp.draw(VP1);

    spe.draw(VP1);

    for(int i =0;i<10;i++)
    	fuelup[i].draw(VP);

    s1[0].draw(VP1,height1);
    s1[1].draw(VP1,height2);

    s2[1].draw(VP1,height3);
    s2[0].draw(VP1,height4);

     if(cp==1)
     	cp1.draw(VP);
     
     if(cp==2)
     	cp2.draw(VP);
     
     if(cp==3)
     	cp3.draw(VP);
     
     if(cp==4)
     	cp4.draw(VP);

}


void tick_input(GLFWwindow *window) {

    int forward  = glfwGetKey(window, GLFW_KEY_W);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int cam1 = glfwGetKey(window, GLFW_KEY_1);
    int cam2 = glfwGetKey(window, GLFW_KEY_2);
    int cam3 = glfwGetKey(window, GLFW_KEY_3);
    int cam4 = glfwGetKey(window, GLFW_KEY_4);
    int cam5 = glfwGetKey(window, GLFW_KEY_5);
    int rightturn = glfwGetKey(window, GLFW_KEY_D);
    int leftturn = glfwGetKey(window, GLFW_KEY_A);
    int righttilt = glfwGetKey(window, GLFW_KEY_RIGHT);
    int lefttilt = glfwGetKey(window, GLFW_KEY_LEFT);
    int miss = glfwGetKey(window, GLFW_KEY_M); 
    int bom = glfwGetKey(window, GLFW_KEY_B); 
    int loop = glfwGetKey(window, GLFW_KEY_L); 

    if(loop)
    {
    	if(aero.position.z >=0)
    	{
    	aero.loopin = 1;

    	aero.position.y +=0.2;
    	aero.position.z -= 0.3;
        }
        else if(aero.position.z <= 0 && aero.position.y >= 20)
    	{
    	aero.loopin = 2;
        //cout<<"pls work"<<endl;
    	aero.position.y -=0.2;
    	aero.position.z -= 0.3;
    	} 

    	else if( aero.position.y < 20)
    	{
    	aero.loopin = 3;
        //cout<<"pls pls work correctly"<<endl;
    	//aero.position.y -=0.1;
    	aero.position.z += 0.2;
    	} 
    }

    if(miss)
    {
    	chk=1;
    	tarit = 1;
    	missile.position.x = aero.position.x;
    	missile.position.y = aero.position.y+1;
    	missile.position.z = aero.position.z+1;
        missile.rotation = cr;
        tar.position.x = aero.position.x + 3;
        tar.position.y = aero.position.y + 3;
        tar.position.z = aero.position.z + 3;

    }

    if(bom)
    {
    	chk1=1;
    	bomb.position.x = aero.position.x;
    	bomb.position.y = aero.position.y+1;
    	bomb.position.z = aero.position.z+1;
    }

    if(forward)
    {
    	acc += 0.0001;
    	glm::vec4 final_pos = aero.rotate1 * glm::vec4(0.0f,0.0f,-(0.03f+acc),1);
   		aero.position.x = final_pos[0] + aero.position[0];
   		aero.position.y = final_pos[1] + aero.position[1];
   		aero.position.z = final_pos[2] + aero.position[2];
   		spea += 0.1;
    	spe.rotation = spea;
    	aero.loopin = 0;


    }

    if(up)
    {
    	aero.position.y += 0.04;
    	acc=0;
    	ht=(int)aero.position.y;
    	spea=0;
    	spe.rotation = spea;
    	aero.loopin = 0;
        
    }

    if(down)
    {
    	aero.position.y -= 0.04;
    	acc=0;
    	ht=(int)aero.position.y;
    	spea=0;
    	spe.rotation = spea;
    	aero.loopin = 0;
        
    }

    if(cam1)
    {
        view=0;
    }

    if(cam2)
    {
        view=1;
    }

    if(cam3)
    {
        view=2;
    }

    if(cam4)
    {
        view=3;
    }

    if(cam5)
    {
        view=4;
    }

    if(rightturn)
    {
    	acc=0;
    	aero.direction = 1;
    	cr1 = -1;
    	cr -= 1;
    	aero.rotation = cr1;
    	comp.rotation = cr;
    	spea=0;
    	spe.rotation = spea;
    	aero.loopin = 0;

    }

    if(leftturn)
    {
    	acc=0;
    	aero.direction = 1;
    	cr1=1;
    	cr +=1;
    	aero.rotation = cr1;
    	comp.rotation = cr;
    	spea=0;
    	spe.rotation = spea;
    	aero.loopin = 0;


    }

    if(righttilt)
    {
    	acc=0;
    	aero.rotation += 1;
    	cr = cr;
    	aero.direction = 2;
    	spea=0;
    	spe.rotation = spea;
    	aero.loopin = 0;


    }

    if(lefttilt)
    {
    	acc=0;
    	aero.rotation -= 1;
    	cr = cr;
    	aero.direction = 2;
    	spea=0;
    	spe.rotation = spea;
    	aero.loopin = 0;
        
    }

    if (drag_pan) 
    {
        if (drag_oldx == -1 || drag_oldy == -1) 
        {
            glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
        } 
        else 
        {
            double newx, newy;
            glfwGetCursorPos(window, &newx, &newy);
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            if(8 * (newx - drag_oldx) / (width * screen_zoom)<0)
              camera_rotation_angle-=0.1;
            else if(8 * (newx - drag_oldx) / (width * screen_zoom)>0)
                camera_rotation_angle+=0.1;
            if(8 * (newy - drag_oldy) / (height * screen_zoom)<0)
                r-=0.3;

            drag_oldx = newx;
            drag_oldy = newy;
        }
    }
}


void tick_elements() {

    height1= ht % 10;
    height2= ht / 10;

    height3= fu % 10;
    height4= fu / 10;

    float dist;

    for(int i =0;i<20;i++)
    	if(gu[i]==1)
    		gun[i].tick();

    for(int i=0;i<60;i++)
    {
    	dist = pow((aero.position.z-para[i].position.z),2)+pow((aero.position.x-para[i].position.x),2);
    	if(dist <= 400)
    		pchk[i]=1;
    }

    	if(cp==1 && aero.position.x <= -40 && aero.position.z >= 40)
    		{   
    			for(int i=5;i<10;i++)
    			{
    			gu[i]=1;
    		    
    		}
    		}

        if(cp==2 && aero.position.x >= 40 && aero.position.z >= 40)
            {
    			for(int i=0;i<5;i++)
    			{
    			gu[i]=1;
    		    }
    		}

    	if(cp==3 && aero.position.x >= 40 && aero.position.z <= -40)
    		{
    			for(int i=15;i<20;i++)
    			{
    			gu[i]=1;
    		    }
    		}

    	if(cp==4 && aero.position.x <= -40 && aero.position.z <= -40)
            {
    			for(int i=10;i<15;i++)
    			{
    			gu[i]=1;
    		    }
    		}

    for(int i=0;i<60;i++)
    	if(pchk[i]==1)
    		para[i].tick();

    if(aero.position.z >= 0 && chk==1)
        missile.tick1();

    if(aero.position.z <0 && chk==1)
        missile.tick();

    if(chk1==1)
    	bomb.tick();
     
    //cout<<aero.position.x <<" "<<aero.position.z << endl;

    if(cp==1 && aero.position.x <= -40 && aero.position.z >= 40)
    	{
    	cp=2;
    	level = 2;
    	}

    if(cp==2 && aero.position.x >= 40 && aero.position.z >= 40)
    	{
    	cp=3;
    	level = 3;
    	}

    if(cp==3 && aero.position.x >= 40 && aero.position.z <= -40)
    	{
    	cp=4;
    	level = 4;
    	}

    if(cp==4 && aero.position.x <= -40 && aero.position.z <= -40)
    	{
    	cp=5;
    	level = 5;
    	}


if(health <= 0)
    {
         cout<<"OOPS U LOST :/"<< " "<< " your score is : "<<score<<endl;
        quit(window);
    }

if(fuel <= 0 )
    {
         cout<<"OOPS U LOST :/"<< " "<< " your score is : "<<score<<endl;
        quit(window);
    }

 if(aero.position.y < 0 )
    {
         cout<<"OOPS U LOST :/"<< " "<< " your score is : "<<score<<endl;
        quit(window);
    }

 if(aero.position.z <= -85 && level ==5)
    {
        cout<<"CONGRATS U WON !!!"<< " "<< " your score is : "<<score<<endl;
        quit(window);
    }



// Bounding box conditions
    
    for(int i=0;i<20;i++)
    {

     if(detect_collision(gun[i].getstruct(),aero.getstruct())!=0)
        {
           health-=1;
           gun[i].position.y = 10000;
           
        }
    }

    for(int i=0;i<20;i++)
    {

     if(detect_collision(gun[i].getstruct(),missile.getstruct())!=0)
        {
        	score+=15;
           gun[i].position.y = 10000;
           
        }
    }

    for(int i=0;i<80;i++)
    {

     if(detect_collision(enemy[i].getstruct(),bomb.getstruct())!=0)
        {
           enemy[i].position.y = -10000;
           
        }
    }

    for(int i=0;i<5;i++)
    {

     if(detect_collision(enemyc[i].getstruct(),bomb.getstruct())!=0)
        {
           enemyc[i].position.y = -10000;
           guncp1[i]=1;
           
        }
    }

    for(int i=5;i<10;i++)
    {

     if(detect_collision(enemyc[i].getstruct(),bomb.getstruct())!=0)
        {
           enemyc[i].position.y = -10000;
           guncp2[i]=1;
           
        }
    }

    for(int i=10;i<15;i++)
    {

     if(detect_collision(enemyc[i].getstruct(),bomb.getstruct())!=0)
        {
           enemyc[i].position.y = -10000;
           guncp3[i]=1;
        }
    }

    for(int i=15;i<20;i++)
    {

     if(detect_collision(enemyc[i].getstruct(),bomb.getstruct())!=0)
        {
           enemyc[i].position.y = -10000;
           guncp4[i]=1;
        }
    }

    for(int i=80;i<88;i++)
    {

     if(detect_collision(enemy[i].getstruct1(),aero.getstruct1())!=0)
        {
           //enemy[i].position.y = -10000;
           cout<<"OOPS U LOST :/"<< " "<< " your score is : "<<score<<endl;
           quit(window);

           
        }
    }

    for(int i=0;i<10;i++)
    {

     if(detect_collision(fuelup[i].getstruct(),aero.getstruct())!=0)
        {
           fuelup[i].position.y = -10000;
           fu += 5;
           
        }
    }

    for(int i=0;i<10;i++)
    {

     if(detect_collision(ring[i].getstruct(),aero.getstruct())!=0)
        {
           //ring[i].position.y = -10000;
        	if(ringo[i]==0)
        	{
             score += 20;
             ringo[i]=1;
            }
        }
    }
 
    for(int i=0;i<60;i++)
    {

     if(detect_collision(para[i].getstruct(),missile.getstruct())!=0)
        {
           para[i].position.y = -10000;
           score += 30;
           
        }
    }

    for(int i=0;i<60;i++)
    {

     if(detect_collision(para[i].getstruct(),aero.getstruct())!=0)
        {
           para[i].position.y = -10000;
           health -= 1;
        }
    }




}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    land=Land(0,0,COLOR_GREEN);

    sea=Sea(0,0,COLOR_LBLUE);

    tar = Tar(aero.position.x+3,aero.position.y+3,aero.position.z+3,COLOR_BLACK);

    aero=Aero(0,0.5,85,0.3,COLOR_BLACK,0,0,0);

    comp=Comp(3,0,3,0,COLOR_BLACK,COLOR_RED, COLOR_BLUE);

    spe=Speed(-3,0,3,0,COLOR_BLACK,COLOR_RED, COLOR_BLUE);

    circ=Circ(3,0,3,0,COLOR_BLACK,COLOR_RED, COLOR_BLUE);

    s1[1]=Score(-3.4,0,-3.0,COLOR_BLACK);
    s1[0]=Score(-3.0,0,-3.0,COLOR_BLACK);
    s2[1]=Score(3.4,0,-3.0,COLOR_BLACK);
    s2[0]=Score(3.0,0,-3.0,COLOR_BLACK);

    missile=Missile(aero.position.x,aero.position.y+1,aero.position.z+1,0.1,COLOR_BLACK,aero.rotation,0);

    bomb=Bomb(aero.position.x,aero.position.y,aero.position.z,0.225,COLOR_BLACK,0,0);

    cp1=Chk(-60,20,40,1,COLOR_RED);
    cp2=Chk(60,20,40,1,COLOR_RED);
    cp3=Chk(60,20,-40,1,COLOR_RED);
    cp4=Chk(-60,20,-40,1,COLOR_RED);

    enemyc[0] = Enemyc(55,0,55,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[1] = Enemyc(45,0,45,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[2] = Enemyc(40,0,40,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[3] = Enemyc(50,0,50,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[4] = Enemyc(60,0,60,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[5] = Enemyc(-54,0,54,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[6] = Enemyc(-52,0,56,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[7] = Enemyc(-56,0,52,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[8] = Enemyc(-50,0,50,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[9] = Enemyc(-58,0,58,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[10] = Enemyc(-55,0,-55,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[11] = Enemyc(-45,0,-45,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[12] = Enemyc(-40,0,-40,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[13] = Enemyc(-50,0,-50,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[14] = Enemyc(-60,0,-60,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[15] = Enemyc(54,0,-54,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[16] = Enemyc(52,0,-56,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[17] = Enemyc(56,0,-52,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[18] = Enemyc(50,0,-50,0.75,COLOR_purple,COLOR_FIRE);
    enemyc[19] = Enemyc(58,0,-58,0.75,COLOR_purple,COLOR_FIRE);

    gun[0] = Gun(55,2,55,0.75,COLOR_CRIMSON);
    gun[1] = Gun(45,2,45,0.75,COLOR_CRIMSON);
    gun[2] = Gun(40,2,40,0.75,COLOR_CRIMSON);
    gun[3] = Gun(50,2,50,0.75,COLOR_CRIMSON);
    gun[4] = Gun(60,2,60,0.75,COLOR_CRIMSON);
    gun[5] = Gun(-54,2,54,0.75,COLOR_CRIMSON);
    gun[6] = Gun(-52,2,56,0.75,COLOR_CRIMSON);
    gun[7] = Gun(-56,2,52,0.75,COLOR_CRIMSON);
    gun[8] = Gun(-50,2,50,0.75,COLOR_CRIMSON);
    gun[9] = Gun(-58,2,58,0.75,COLOR_CRIMSON);
    gun[10] = Gun(-55,2,-55,0.75,COLOR_CRIMSON);
    gun[11] = Gun(-45,2,-45,0.75,COLOR_CRIMSON);
    gun[12] = Gun(-40,2,-40,0.75,COLOR_CRIMSON);
    gun[13] = Gun(-50,2,-50,0.75,COLOR_CRIMSON);
    gun[14] = Gun(-60,2,-60,0.75,COLOR_CRIMSON);
    gun[15] = Gun(54,2,-54,0.75,COLOR_CRIMSON);
    gun[16] = Gun(52,2,-56,0.75,COLOR_CRIMSON);
    gun[17] = Gun(56,2,-52,0.75,COLOR_CRIMSON);
    gun[18] = Gun(50,2,-50,0.75,COLOR_CRIMSON);
    gun[19] = Gun(58,2,-58,0.75,COLOR_CRIMSON);
    
    int a,b;
    int c = 1;
    int f = 70;
    int u =-1;

    flag1=Flag(0,5.8,-89,2,COLOR_BLACK);

    for(int i =0;i<10;i++)
    {
    	u*=-1;
    	fuelup[i]=Fuel(f,13,(u*(rand()%57)),0.4,COLOR_maroon);
    	f-=17;
    }

    for(int i =0;i<10;i++)
    {   
    	c = c*-1;
    	a=rand()%3;
    	//a=a*c;
    	b=rand()%3;
    	//b=b*c;
    	hill[i]=Hill(a+5,0,b+5,0.5,COLOR_BROWN);
    }
    	enemy[80]=Enemy(7,0,7,3.75,COLOR_lGREEN);

    for(int i =10;i<20;i++)
    {   
    	c = c*-1;
    	a=rand()%4;
    	//a=a*c;
    	b=rand()%4;
    	//b=b*c;
    	hill[i]=Hill(a-25,0,b+5,0.5,COLOR_BROWN);
    }
    	enemy[81]=Enemy(-23,0,7,3.75,COLOR_lGREEN);

    for(int i =20;i<30;i++)
    {   
    	c = c*-1;
    	a=rand()%5;
    	//a=a*c;
    	b=rand()%5;
    	//b=b*c;
    	hill[i]=Hill(a+5,0,b+40,0.5,COLOR_BROWN);
    }
    	enemy[82]=Enemy(7,0,42,3.75,COLOR_lGREEN);

    for(int i =30;i<40;i++)
    {   
    	c = c*-1;
    	a=rand()%3;
    	//a=a*c;
    	b=rand()%3;
    	//b=b*c;
    	hill[i]=Hill(a+59,0,b+66,0.5,COLOR_BROWN);
    }
    	enemy[83]=Enemy(61,0,68,3.75,COLOR_lGREEN);

    for(int i =40;i<50;i++)
    {   
    	c = c*-1;
    	a=rand()%3;
    	//a=a*c;
    	b=rand()%3;
    	//b=b*c;
    	hill[i]=Hill(a+5,0,-(b+5),0.5,COLOR_BROWN);
    }
    	enemy[84]=Enemy(7,0,-7,3.75,COLOR_lGREEN);

    for(int i =50;i<60;i++)
    {   
    	c = c*-1;
    	a=rand()%4;
    	//a=a*c;
    	b=rand()%4;
    	//b=b*c;
    	hill[i]=Hill(a-25,0,-(b+5),0.5,COLOR_BROWN);
    }
    	enemy[85]=Enemy(-23,0,-7,3.75,COLOR_lGREEN);


    for(int i =60;i<70;i++)
    {   
    	c = c*-1;
    	a=rand()%5;
    	//a=a*c;
    	b=rand()%5;
    	//b=b*c;
    	hill[i]=Hill(a+5,0,-(b+40),0.5,COLOR_BROWN);
    }
    	enemy[86]=Enemy(7,0,-42,3.75,COLOR_lGREEN);


    for(int i =70;i<80;i++)
    {   
    	c = c*-1;
    	a=rand()%3;
    	//a=a*c;
    	b=rand()%3;
    	//b=b*c;
    	hill[i]=Hill(a+59,0,-(b+66),0.5,COLOR_BROWN);
    }
    	enemy[87]=Enemy(61,0,-68,3.75,COLOR_lGREEN);
     
    for(int i =0;i<10;i+=2)
    {
    	c=c*-1;
    	a = rand()%7;
    	ring[i]=Ring(0,15+a,-(c*(8*i+5)),1.0,COLOR_BLACK);
    	ring[i+1]=Ring(0,15+a,-(c*(8*i+5)),0.8,COLOR_white);

    }

    for(int i =0;i<40;i++)
    {   
    	c = c*-1;
    	a=rand()%70;
    	a=a*c;
    	b=rand()%70;
    	//if(i%2==0)
    	b=b*c;
    	enemy[i]=Enemy(a,0,b,0.75,COLOR_BLUE);
    }

    for(int i =40;i<80;i++)
    {   
    	c = c*-1;
    	a=rand()%70;
    	a=a*c;
    	b=rand()%70;
    	//if(i%2==0)
    	b=b*c;
    	enemy[i]=Enemy(a,0,-b,0.75,COLOR_BLUE);
    }

    for(int i =0;i<30;i++)
    {   
    	c=c*-1;
    	a= rand()%57;
    	b= rand()%57;
    	b=b*c;
    	a=a*c;
    	para[i]=Para(a,60,b,1.0,COLOR_GREEN,0.01);
    }

    for(int i =30;i<60;i++)
    {   
    	c=c*-1;
    	a= rand()%57;
    	b= rand()%57;
    	b=b*c;
    	a=a*c;
    	para[i]=Para(a,60,-b,1.0,COLOR_GREEN,0.01);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {

    srand(time(0));
    int width  = 600;
    int height = 600;
    char stringPrint[1000];

    window = initGLFW(width, height);

    initGL (window, width, height);

    Matrices.projection = glm::perspective(glm::radians(screen_zoom),(float)600/(float)600,0.1f,100.0f);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            sprintf(stringPrint, "Level: %d  Score: %d Health: %d", level, score, health);
           
            glfwSetWindowTitle(window, stringPrint);

            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        if(tfu.processTick())
        	{
        		fu--;
        	}

        if(tsco.processTick())
        	{
        		score+=2;
        	}

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.depth + b.depth));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
     Matrices.projection = glm::perspective(35.f,1.0f, 0.1f, 500.0f);
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
