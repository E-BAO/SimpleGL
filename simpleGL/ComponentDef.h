//
//  ComponentDef.hpp
//  simpleGL
//
//  Created by EBAO on 2017/5/27.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#ifndef _COMPONENTDEF_H_
#define _COMPONENTDEF_H_

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

typedef struct Color color_s;

struct Color{
    float r,g,b,a;
    Color(){};
    
//    Color(const Color &c2) {
//        this->r = c2.r;
//        this->g = c2.g;
//        this->b = c2.b;
//        this->a = c2.a;
//    }
    
    Color(float r,float g,float b,float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    
    
    //    Color(Color &c2){
    //        r = c2.r;
    //        g = c2.g;
    //        b = c2.b;
    //        a = c2.a;
    //    }
    
    Color& operator+=(Color &c2){
        r = r * a + c2.r * c2.a;
        g = g * a + c2.g * c2.a;
        b = b * a + c2.b * c2.a;
        return *this;
    }
    
    Color operator-(){
        return Color(-r,-g,-b,1.0);
    }
    
//    Color& operator = (Color &c2){
//        this->r = c2.r;
//        this->g = c2.g;
//        this->b = c2.b;
//        this->a = c2.a;
//        return *this;
//    }
//    
    Color& operator -= (Color &c2){
        Color res = -c2;
        return operator+=(res);
    }
    
    friend Color operator+(Color &c1,Color &c2);
    friend Color operator-(Color &c1,Color &c2);
    friend Color operator*(Color &c1,Color &c2);
    friend Color operator*(Color &c,float f);
    
};

inline Color operator+(Color &c1,Color &c2){
    return Color( c1.r * c1.a + c2.r * c2.a,
                 c1.g * c1.a + c2.g * c2.a,
                 c1.b * c1.a + c2.b * c2.a,1.0);
}

inline Color operator-(Color &c1,Color &c2){
    return Color( c1.r * c1.a - c2.r * c2.a,
                 c1.g * c1.a - c2.g * c2.a,
                 c1.b * c1.a - c2.b * c2.a,1.0);
}

inline Color operator*(Color &c1,Color &c2){
    return Color( c1.r * c2.r,
                 c1.g * c2.g,
                 c1.b * c2.b,
                 c1.a * c2.a);
}

inline Color operator*(Color &c,float f){
    return Color(c.r * f,c.g * f,c.b * f,1.0);
}

typedef struct Vector vector_s;

typedef vector_s point_s;

struct Vector{
    float x,y,z,w;
    Vector(){};
    Vector(float x,float y,float z,float w = 1.0) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    vector_s operator-(){
        return vector_s(-x,-y,-z,-w);
    }
    
    float length(){
        return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
    }
    
    void normalize(){
        float l = length();
        if(l){
            float f = (float)1.0f/l;
            x *= f;
            y *= f;
            z *= f;
        }
    }
    
    void devWeight(){
        float inv_w = 1.0 / w;
        x *= inv_w;
        y *= inv_w;
        z *= inv_w;
        w = 1.0;
    }
    
    void print(){
        cout<<"("<<x<<","<<y<<","<<z<<","<<w<<")"<<endl;
    }
    
    vector_s crossMul(vector_s v2){
        vector_s res;
        res.x = y * v2.z - z * v2.y;
        res.y = z * v2.x - x * v2.z;
        res.z = x * v2.y - y * v2.x;
        res.w = 1.0f;
        return res;
    }
    
    friend float operator*(vector_s &v1,vector_s &v2);
    friend vector_s operator*(vector_s &v1,float f);
    friend vector_s operator-(vector_s &v1,vector_s &v2);
    friend vector_s operator+(vector_s &v1,vector_s &v2);
};

inline float operator*(vector_s &v1,vector_s &v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vector_s operator*(vector_s &v1,float f){
    return vector_s(v1.x * f,v1.y * f,v1.z * f,1.0);
}

inline vector_s operator+(vector_s &v1,vector_s &v2){
    return vector_s(v1.x + v2.x,v1.y + v2.y,v1.z + v2.z,1.0);
}

inline vector_s operator-(vector_s &v1,vector_s &v2){
    return vector_s(v1.x - v2.x,v1.y - v2.y,v1.z - v2.z,1.0);
}

typedef struct Vertex{
    color_s color;
    point_s pos;
    Vertex(){};
    Vertex(Vertex &v){
        color = v.color;
        pos = v.pos;
    }
}vertex_s;

typedef struct{
    int type;
    int a;
    int b;
}pair_s;

typedef struct Matrix{
    float m[4][4];

    void setIdentity(){
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++)
                m[i][j] = (i == j);
    }
    
    void setZero(){
        memset(m, 0.0, sizeof(float)*4*4);
    }
    
    Matrix operator-(){
        Matrix res;
        for(int i = 0;i < 4;i ++)
            for(int j = 0;j < 4;j++)
                res.m[i][j] = - m[i][j];
        return res;
    }
    
    Matrix& operator*=(Matrix& m2){
        Matrix res = *this * m2;
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++)
                m[i][j] = res.m[i][j];
        return *this;
    }
    
    Matrix inverse(){
        float middle[4][4];
        float res[4][4];
        
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++){
                middle[i][j] = m[i][j];
                res[i][j] = (i == j);
            }
        
        Matrix mat;
        
        pair_s pair[6];
        int swapTime = 0;
        
        for(int i = 0;i < 3;i++){
            float pivot = middle[i][i];
            int row = i;
            int col = i;
            //find max pivot
            for(int l = i;l < 4;l++)
                for(int k = i;k < 4;k++)
                    if(fabs(middle[l][k]) > fabs(pivot)){
                        pivot = middle[l][k];
                        row = l;
                        col = k;
                    }
            
            if(fabs(pivot) < 1e-6){
                std::cout<<"matrix inverse error"<<std::endl;
                exit(0);
            }
            
            if(row != i) {// swap i and col row
                pair[swapTime].type = 1;
                pair[swapTime].a = row;
                pair[swapTime].b = i;
                for(int ii = 0;ii < 4;ii++){
                    swap(middle[i][ii],middle[row][ii]);
                    swap(res[i][ii],res[row][ii]);
                }
                swapTime++;
            }
            
            if(col != i){
                pair[swapTime].type = 2;
                pair[swapTime].a = col;
                pair[swapTime].b = i;
                for(int jj = 0;jj < 4;jj++){
                    swap(middle[jj][col],middle[jj][i]);
                    //swap(res[jj][col],res[jj][i]);
                }
                swapTime++;
            }
            
            float a = middle[i][i];
            
            for(int j = 0;j < 4;j++){
                middle[i][j] /= a;
                res[i][j] /= a;
            }
            for(int j = i + 1;j < 4;j++){

                float b = -middle[j][i];

                for(int k = 0;k < 4;k++){
                    middle[j][k] += middle[i][k] * b;
                    res[j][k] += res[i][k] * b;
                }
            }
        }
        
        if(fabs(middle[3][3]) < 1e-6){
            std::cout<<"matrix inverse error1"<<std::endl;
            exit(0);
        }
        
        for(int i = 3;i > 0;i--){
            float c = middle[i][i];
            if(fabs(c) < 1e-6){
                std::cout<<"matrix inverse error2"<<std::endl;
                exit(0);
            }
            for(int k = 0;k < 4;k++){
                res[i][k] /= c;
                middle[i][k] /= c;
            }
            for(int j = i - 1;j >= 0;j--){
                float d = -middle[j][i];
                for(int k = 0;k < 4;k++){
                    middle[j][k] += middle[i][k] * d;
                    res[j][k] += res[i][k] * d;
                }
            }
        }
        
        for(int i = swapTime - 1;i >= 0;i--){
            int a = pair[i].a;
            int b = pair[i].b;
            if(pair[i].type == 2){//
                for(int ii = 0;ii < 4;ii++)
                    swap(res[a][ii],res[b][ii]);
            }
//            else{
//                for(int ii = 0;ii < 4;ii++)
//                    swap(res[ii][a],res[ii][b]);
//            }
        }

        memcpy(&mat.m,&res, sizeof(float) * 16);
        
        return mat;
    }
    
    Matrix transpose(){
        Matrix newM;
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++)
                newM.m[i][j] = this->m[j][i];
        //newM.print();
        return newM;
    }
    
    void preMultiply(Matrix& m2){
        Matrix res = m2 * (*this);
        for(int i = 0;i < 4;i++)
            for(int j = 0;j < 4;j++)
                m[i][j] = res.m[i][j];
    }
    
    void print(){
        cout<<"----------"<<endl;
        for(int i = 0;i < 4;i++){
            cout<<"| ";
            for(int j = 0;j < 4;j++){
                cout<<m[i][j]<<" ";
            }
            cout<<"|"<<endl;
        }
        cout<<"----------"<<endl;
    }
    
    friend Matrix operator+(Matrix &c1,Matrix &c2);
    friend Matrix operator-(Matrix &c1,Matrix &c2);
    friend Matrix operator*(Matrix &c1,Matrix &c2);
    friend vector_s operator*(Matrix &c1,vector_s &v);
}matrix_s;

inline Matrix operator+(Matrix &c1,Matrix &c2){
    Matrix res;
    for(int i = 0;i < 4;i ++)
        for(int j = 0;j < 4;j++){
            res.m[i][j] = c1.m[i][j] + c2.m[i][j];
        }
    return res;
}

inline Matrix operator-(Matrix &c1,Matrix &c2){
    Matrix cc2 = -c2;
    return c1 + cc2;
}

inline Matrix operator*(Matrix &c1,Matrix &c2){
    Matrix res;
    for(int i = 0;i < 4;i ++)
        for(int j = 0;j < 4;j++){
            res.m[i][j] = c1.m[i][0] * c2.m[0][j] + c1.m[i][1] * c2.m[1][j] + c1.m[i][2] * c2.m[2][j] + c1.m[i][3] * c2.m[3][j];
        }
    return res;
}

inline vector_s operator*(Matrix &c1,vector_s &v){
    float res[4] = {0.0,0.0,0.0,0.0};
    float vf[4] = {v.x,v.y,v.z,v.w};
    for(int i = 0;i < 4;i++)
        for(int j = 0;j < 4;j++){
            res[i] += c1.m[i][j] * vf[j];
        }
    return vector_s(res[0],res[1],res[2],res[3]);
}

typedef struct Vertex2i{
    int x,y;
    float z;
    color_s color;
    Vertex2i(){};
    Vertex2i(Vertex2i const &v){
        x = v.x;
        y = v.y;
        z = v.z;
        color = v.color;
    }
}vertex2i;

typedef struct{
    int left;
    int right;
    float zleft;
    float zright;
    color_s cleft;
    color_s cright;
    void init(int win_width,color_s background){
        left = win_width + 1;
        right = -1;
        zleft = zright = 1.0;
        cleft = cright = background;
    }
    
    void update(int x,float z,color_s c){
        if(x < left){
            left = x;
            zleft = z;
            cleft = c;
        }
        if(x > right){
            right = x;
            zright = z;
            cright = c;
        }
    }
}scanline_s;

#endif /* _COMPONENTDEF_H_ */
