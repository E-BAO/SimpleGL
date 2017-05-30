//
//  Renderer.cpp
//  simpleGL
//
//  Created by EBAO on 2017/5/27.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#include "Renderer.h"

void Renderer::init(){
    transform.world.setIdentity();
    setLookAt(point_s(0.0,0.0,0.0,1.0), point_s(0.0,0.0,-1.0,1.0), point_s(0.0,1.0,0.0,1.0));
    setPerspective(90, 1, -1, -50);
    clearBuffer(color_s(0.0,0.0,0.0,1.0));
}

void Renderer::clearBuffer(color_s color){
    if(fabs(color.r) < 1e-6 && fabs(color.g) < 1e-6 && fabs(color.b) < 1e-6)
        memset(frameBuffer, 0.0, sizeof(float) * MAX_WIDTH * MAX_HEIGHT * 3);
    else{
        for(int i = 0;i < MAX_HEIGHT;i++)
            for(int j = 0;j < MAX_WIDTH;j++){
                frameBuffer[i * MAX_WIDTH + j][0] = color.r;
                frameBuffer[i * MAX_WIDTH + j][1] = color.g;
                frameBuffer[i * MAX_WIDTH + j][2] = color.b;
            }
    }
    background = color;
    memset(zBuffer, 1e6, sizeof(zBuffer));
}

scanline_s scanlines[MAX_HEIGHT];

void Renderer::drawTriangle(vertex_s vertex[3]){
    
    point_s v[3];
    vertex2i vi[3];
    
    for(int i = 0;i < 3;i++){
        point_s v = transform.totalTransform * vertex[i].pos;
        v.devWeight();
        v.print();
        bool flag = is_out_of_range(v);
        if(flag)return;
        vi[i].x = win_width / 2 + v.x * (float)(win_width / 2);
        vi[i].y = win_height / 2 + v.y * (float)(win_height / 2);
        vi[i].z = v.z;
        vi[i].color = vertex[i].color;
    }
    
    triangleRange(vi);
    
    float m = (float)(vi[0].x - vi[2].x) / (float)(vi[0].y - vi[2].y);
    float width = vi[1].x - (m * (float)(vi[1].y - vi[0].y) + vi[0].x);
    float step_up = (vi[0].y == vi[1].y? width:width / (vi[0].y - vi[1].y));
    float step_down = (vi[1].y == vi[2].y ? width:- width / (vi[1].y - vi[2].y));
    //std::cout<<"width = "<<width<<"up = "<<step_up<<" down = "<<step_down<<std::endl;

    int dy = vi[0].y - vi[2].y + 1;
    float strip = vi[1].y == vi[0].y ? width:0;
    int y = vi[0].y;
    float x = vi[0].x;
    
    for(int i = 0;i < dy;i++){
        scanlines[y - i].init(win_width,background);
    }
    
    drawLines(vertex, 3, LINE_LOOP);
    
    for(int i = 0;i < dy;i++ ){
        //std::cout<<"y = "<<y - i<<" strip = "<<strip<<std::endl;
        if(scanlines[y - i].left > scanlines[y - i].right)continue;
        drawScanLine(y - i,scanlines);
    }
}

void Renderer::triangleRange(vertex2i vi[3]){
    if(vi[1].y < vi[2].y )
        swap(vi[1], vi[2]);
    if(vi[0].y < vi[1].y)
        swap(vi[0], vi[1]);
    if(vi[1].y < vi[2].y )
        swap(vi[1], vi[2]);
}

void Renderer::drawScanLine(int y,scanline_s* scanline){
    int x1 = scanlines[y].left;
    int x2 = scanlines[y].right;
    color_s c1 = scanlines[y].cleft;
    color_s c2 = scanlines[y].cright;
    float z1 = scanlines[y].zleft;
    float z2 = scanlines[y].zright;
    
    color_s color = c1;
    color_s dc = c2 - c1;
    dc = dc * (1.0/(float)(x2 - x1));
    float z = z1;
    float dz = (z2 - z1)/(float)(x2 - x1);
    
    for(int i = x1;i <= x2;i++){
        drawPixel(i,y,z,color);
        color += dc;
        z += dz;
    }
}

void Renderer::drawLines(vertex_s vertex[],int N,LineType type){
    vertex2i* v;
    vertex2i vi[3];
    
    for(int i = 0;i < 3;i++){
        point_s v = transform.totalTransform * vertex[i].pos;
        v.devWeight();
        v.print();
        bool flag = is_out_of_range(v);
        if(flag)return;
        vi[i].x = win_width / 2 + v.x * (float)(win_width / 2);
        vi[i].y = win_height / 2 + v.y * (float)(win_height / 2);
        vi[i].z = v.z;
        vi[i].color = vertex[i].color;
    }
    

    int NN = 0;
    switch (type) {
        case LINES:
            NN = (int)floor((float)N * 0.5f) * 2;
            v = new vertex2i[NN];
            for (int i = 0; i < NN; i++)
                v = &vi[i];
            break;
        case LINE_STRIPE:
            NN = N * 2 - 2;
            v = new vertex2i[NN];
            v[0] = vi[0];
            for (int i = 1; i < N - 1; i++)
                v[2 * i - 1] = v[2 * i] = vi[i];
            v[NN - 1] = vi[N - 1];
            break;
        case LINE_LOOP:
            NN = N * 2;
            v = new vertex2i[NN];
            v[0] = vi[0];
            for (int i = 1; i < N; i++)
                v[2 * i - 1] = v[2 * i] = vi[i];
            v[NN - 1] = vi[0];
            break;
        default:
            break;
    }
    
//    std::cout<<"vi[0]"<<vi[0].color.r<<std::endl;
    
    for(int i = 0;i < NN / 2;i++){
        int x1 = v[2 * i].x;
        int x2 = v[2 * i + 1].x;
        int y1 = v[2 * i].y;
        int y2 = v[2 * i + 1].y;

        color_s c1 = v[2 * i].color;
        color_s c2 = v[2 * i + 1].color;
        float z1 = v[2 * i].z;
        float z2 = v[2 * i + 1].z;
        
        drawLine(x1, y1, z1, c1, x2, y2, z2, c2);
    }
    
    if(v){
        delete v;
        v = NULL;
    }
}

//DDA algorithm
void Renderer::drawLine(int x1,int y1,float z1,color_s color1,int x2,int y2,float z2,color_s color2){
    if(x1 == x2){ // vertical
        if(y1 > y2){
            swap(y1, y2);
            swap(z1, z2);
            swap(color1, color2);
        }
        if(y1 < 0)return;
        float dp = 1.0/(float)(y2 - y1);
        color_s color = color1;
        color_s dc = color2 - color1;
        dc = dc * dp;
        float dz = (z2 - z1) * dp;
        float z = z1;
        for(int i = y1;i <= y2;i++){
            color += dc;
            z += dz;
            scanlines[i].update(x1, z,color);
            drawPixel(x1,i,z,color);
        }
        return;
    }
    
    float k = (float)(y2 - y1)/(float)(x2 - x1);
    
    if(fabs(k) > 1.0){
        k = 1.0 / k;
        if(y1 > y2){
            swap(x1, x2);
            swap(y1, y2);
            swap(z1, z2);
            swap(color1, color2);
        }
        float xf = x1;
        color_s color = color1;
        color_s dc = color2 - color1;
        dc = dc * (1.0/(float)(y2 - y1));
        float z = z1;
        float dz = (z2 - z1)/(float)(y2 - y1);
        for(int j = y1;j <= y2;j++){
            scanlines[j].update((int)xf, z,color);
            drawPixel((int)xf, j,z, color);
            xf += k;
            z += dz;
            color += dc;
        }
    }else{
        if(x1 > x2){
            swap(x1, x2);
            swap(y1, y2);
            swap(color1, color2);
        }
        float yf = y1;
        color_s color = color1;
        color_s dc = color2 - color1;
        dc = dc * (1.0/(float)(x2 - x1));
        double z = z1;
        double dz = (z2 - z2)/(double)(x2 - x1);
//        cout<<"++++++++z"<<z<<endl;

        for(int i = x1;i <= x2;i++){
            scanlines[(int)yf].update(i, z,color);
            drawPixel(i, (int)yf,(float)z, color);
            yf += k;
            z += dz;
            color += dc;
        }
 //       cout<<"_______z"<<z<<endl;
    }
}

//write color value in framebuffer at x,y
void Renderer::drawPixel(int x,int y,float z,color_s color){
    
    if(zBuffer[y * win_width + x] < z)return;
    
    if(x >= 0 && x <= win_width && y >= 0 && y<= win_height){
        frameBuffer[y * win_width + x][0] = color.r;
        frameBuffer[y * win_width + x][1] = color.g;
        frameBuffer[y * win_width + x][2] = color.b;
        zBuffer[y * win_width + x] = z;
    }
}

//==================================
// Coordinate transform
//==================================
void Renderer::setLookAt(point_s eye,point_s center,point_s up){
    float(*m)[4];
    m = transform.view.m;
    vector_s xaxis,yaxis,zaxis;
    
    zaxis = eye - center;
    zaxis.normalize();
    
    xaxis = up.crossMul(zaxis);
    xaxis.normalize();
    
    yaxis = zaxis.crossMul(xaxis);
    
    m[0][0] = xaxis.x;
    m[1][0] = xaxis.y;
    m[2][0] = xaxis.z;
    m[3][0] = - (xaxis * eye);
    
    m[0][1] = yaxis.x;
    m[1][1] = yaxis.y;
    m[2][1] = yaxis.z;
    m[3][1] = - (yaxis * eye);
    
    m[0][2] = zaxis.x;
    m[1][2] = zaxis.y;
    m[2][2] = zaxis.z;
    m[3][2] = - (zaxis * eye);
    
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    m[3][3] = 1.0f;
    
    transform.updateTransform();
}

void Renderer::setPerspective(float fovy,float aspect,float zNear, float zFar){
    transform.projection.setZero();
    fovy = degree2Radio(fovy);
    float fax = 1.0f / tanf(fovy * 0.5f);
    transform.projection.m[0][0] = fax / aspect;
    transform.projection.m[1][1] = fax;
    transform.projection.m[2][2] = (zFar + zNear) / (zNear - zFar);
    transform.projection.m[2][3] = - 2 * zNear * zFar / (zNear - zFar);
    transform.projection.m[3][2] = -1.0;
    
    transform.updateTransform();
}

bool Renderer::is_out_of_range(vector_s v){
    int check = 0;
    if (v.z < -1.0f) check |= 1;
    if (v.z >  1.0f) check |= 2;
    if (v.x < -1.0f) check |= 4;
    if (v.x >  1.0f) check |= 8;
    if (v.y < -1.0f) check |= 16;
    if (v.y >  1.0f) check |= 32;
    return check > 0;
}

void Renderer::setTranslate(float x,float y,float z){
    matrix_s matTranslate;
    matTranslate.setIdentity();
    
    matTranslate.m[0][3] = x;
    matTranslate.m[1][3] = y;
    matTranslate.m[2][3] = z;
    
    transform.world.preMultiply(matTranslate);
    transform.updateTransform();
}

void Renderer::setRotate(float degree,float x1,float y1,float z1,float x2,float y2,float z2){
    float radianAngle = degree2Radio(degree);
    matrix_s matQuatRot;
    vector_s v(x2 - x1,y2 - y1,z2 - z1,1.0);
    v.normalize();
    float cosA = cosf(radianAngle);
    float oneC = 1 - cosA;
    float sinA = sinf(radianAngle);
    float ux = v.x;
    float uy = v.y;
    float uz = v.z;
    
    setTranslate(-x1, -y1, -z1);
    
    matQuatRot.setIdentity();
    matQuatRot.m[0][0] = ux * ux * oneC + cosA;
    matQuatRot.m[0][1] = ux * uy * oneC - uz * sinA;
    matQuatRot.m[0][2] = ux * uz * oneC + uy * sinA;
    matQuatRot.m[1][0] = uy * ux * oneC + uz * sinA;
    matQuatRot.m[1][1] = uy * uy * oneC + cosA;
    matQuatRot.m[1][2] = uy * uz * oneC - ux * sinA;
    matQuatRot.m[2][0] = uz * ux * oneC - uy * sinA;
    matQuatRot.m[2][1] = uz * uy * oneC + ux * sinA;
    matQuatRot.m[2][2] = uz * uz * oneC + cosA;
    
    transform.world.preMultiply(matQuatRot);
    
    setTranslate(x1, y1, z1);
    //can be omited
    //transform.updateTransform();
}

void Renderer::setScale(float xs,float ys,float zs){
    matrix_s matScale;
    matScale.setIdentity();
    
    matScale.m[0][0] = xs;
    matScale.m[1][1] = ys;
    matScale.m[2][2] = zs;
    
    transform.world.preMultiply(matScale);
    transform.updateTransform();
}

