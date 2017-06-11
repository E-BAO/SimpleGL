//
//  SimpleMath.hpp
//  simpleGL
//
//  Created by EBAO on 2017/5/27.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#ifndef _SIMPLEMATH_H_
#define _SIMPLEMATH_H_

#include <iostream>
#include "ComponentDef.h"

using namespace std;

void swap(int &a,int &b);

void swap(color_s &a,color_s &b);

void swap(vertex2i &a,vertex2i &b);

void swap(float &a,float &b);

//template<class T>
//void swap(T& a,T& b);

float degree2Radio(float degree);

float max(float,float);

#endif /* _SIMPLEMATH_H_ */

