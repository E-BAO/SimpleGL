//
//  Renderer.hpp
//  simpleGL
//
//  Created by EBAO on 2017/5/27.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "SimpleMath.h"
#include <iostream>
#include <vector>
using namespace std;

#define MAX_WIDTH 1440
#define MAX_HEIGHT 900

enum LineType{
    LINES,
    LINE_STRIPE,
    LINE_LOOP
};

typedef struct{
    int win_width = 300;
    int win_height = 300;
    float frameBuffer[MAX_WIDTH * MAX_HEIGHT][3];
    float zBuffer[MAX_WIDTH * MAX_HEIGHT];
    color_s background;
    transform_s transform;
    
    void init();
    void clearBuffer(color_s color = color_s(0.0,0.0,0.0,1.0));
    void drawLine(int x1,int y1,float z1,color_s color1,int x2,int y2,float z2,color_s color2);
    void drawPixel(int x,int y,float z,color_s color);
    void drawScanLine(int y,scanline_s* scanline);
    void drawLines(vertex_s vertex[],int N,LineType type);
    void drawTriangle(vertex_s vertex[3]);
    void triangleRange(vertex2i copy[3]);
    void setLookAt(point_s eye,point_s center,point_s up);
    void setPerspective(float fovy,float aspect,float zNear, float zFar);
    void setTranslate(float x,float y,float z);
    void setRotate(float degree,float x1,float y1,float z1,float x2,float y2,float z2);
    void setScale(float xs,float ys,float zs);
    bool is_out_of_range(vector_s v);
}Renderer;

#endif /* _RENDERER_H_ */
