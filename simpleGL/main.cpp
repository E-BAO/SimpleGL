//
//  main.cpp
//  simpleGL
//
//  Created by EBAO on 2017/5/26.
//  Copyright © 2017年 EBAO. All rights reserved.
//

//#include "ComponentDef.h"
#include "Renderer.h"
//#include "SimpleMath.h"
#include <iostream>
#include <GLUT/GLUT.h>
using namespace std;

Renderer renderer;

float af = -1.0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);                   // 清空屏幕
    
    renderer.clearBuffer();
    //Renderer::drawLine(frameBuffer,50,280,color_s(1.0,0.0,0.0,1.0),250,30,color_s(0.0,1.0,0.0,1.0));

    vertex_s vertex[3];
    vertex[0].color = color_s(1.0,0.0,0.0,1.0);
    vertex[1].color = color_s(1.0,0.0,0.0,1.0);
    vertex[2].color = color_s(1.0,0.0,0.0,1.0);
    
    vertex[0].pos = point_s(.6,0,-2,1.0);
    vertex[1].pos = point_s(-0.1,.5,-2.0,1.0);
    vertex[2].pos = point_s(-0.1,0,-2.0,1.0);
    
    vertex_s vertex1[3];
    vertex1[0].color = color_s(0.0,1.0,0.0,1.0);
    vertex1[1].color = color_s(0.0,1.0,0.0,1.0);
    vertex1[2].color = color_s(0.0,1.0,0.0,1.0);
    
    //vertex[3].color = color_s(0.0,1.0,0.0,1.0);
//    vertex1[0].pos = point_s(0,0,-2.5,1.0);
//    vertex1[1].pos = point_s(0,.7,-2.5,1.0);
//    vertex1[2].pos = point_s(0,0,-1.5,1.0);
    vertex1[0].pos = point_s(.6,0,-2.2,1.0);
    vertex1[1].pos = point_s(-0.1,.5,-2.2,1.0);
    vertex1[2].pos = point_s(-0.1,0,-2.2,1.0);
    //renderer.setLookAt(point_s(0.0,0.0,1.0,1.0), point_s(0.0,0.0,0.0,1.0), point_s(0.0,1.0,0.0,1.0));
    
    renderer.drawTriangle(vertex);
    renderer.drawTriangle(vertex1);
    
    glDrawPixels(renderer.win_width,renderer.win_height,GL_RGB,GL_FLOAT,renderer.frameBuffer);
    
//    GLubyte image[1024*768];
//    for(int i=0;i<768;i++)
//        for(int j=0;j<1024;j++)
//            if(i==5)
//                image[i*1024+j]= 255;
//            else
//                image[i*1024+j]= 0;
//    glDrawPixels(1024,768,GL_LUMINANCE,GL_UNSIGNED_BYTE,image);
    
    glutSwapBuffers();                                  // 显示到屏幕
}

void reshape(int w,int h)
{
    renderer.win_width = w;
    renderer.win_height = h;
}

void keyCallback(unsigned char key,int x,int y){
    if(key == 'u'){renderer.setTranslate(0.0, .1, 0.0);}
    if(key == 'd'){renderer.setTranslate(0.0, -.1, 0.0);}
    if(key == 'l'){renderer.setTranslate(-0.1, 0.0, 0.0);}
    if(key == 'r'){renderer.setTranslate(0.1, 0.0, 0.0);}
    if(key == 'f'){renderer.setTranslate(0.0, 0.0, 0.1);}
    if(key == 'b'){renderer.setTranslate(0.0, 0.0, -0.1);}
    if(key == ' '){renderer.setRotate(10, 0,1,-2.0, 0,0,-2.0);}

    display();
}

    
int main (int argc,  char *argv[])
{
    glutInit(&argc, argv);                             // 初始化glut库
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);  // 显示模式RGBA+双缓存
    // 创建一个窗口
    // 标题为"Simple GLUT App"
    int windowHandle = glutCreateWindow("Simple GLUT App");
    // 指定绘制事件回调函数
    
    renderer.init();

    glutKeyboardFunc(&keyCallback);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);                      // 窗口大小变化时

    glutMainLoop();                                     // 进入事件循环
    return 0;
}
