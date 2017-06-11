//
//  SimpleMath.cpp
//  simpleGL
//
//  Created by EBAO on 2017/5/27.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#include "SimpleMath.h"

void swap(int &a,int &b){
    int c = a;
    a = b;
    b = c;
}

void swap(float &a,float &b){
    float c = a;
    a = b;
    b = c;
}

void swap(color_s &a,color_s &b){
    color_s c = a;
    a = b;
    b = c;
}

void swap(vertex2i &a,vertex2i &b){
    vertex2i c = a;
    a = b;
    b = c;
}
//
//template<class T>
//void swap(T& a,T& b){
//    T c = a;
//    a = b;
//    b = c;
//}

float degree2Radio(float degree){
    return degree * M_PI / 180.0f;
}

float max(float a,float b){
    return a > b ? a:b;
}

