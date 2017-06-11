//
//  Scene.hpp
//  simpleGL
//
//  Created by EBAO on 2017/6/9.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#ifndef _SCENE_H_
#define _SCENE_H_

#include "ComponentDef.h"
#include "Object.h"
#include <stdio.h>

class Light{
public:
    Light(){
        pos = point_s(0.0,0.0,3.0,1.0);
        ambient = color_s(1.0,1.0,1.0,1.0);
        diffuse = color_s(1.0,1.0,1.0,1.0);
    }
    
    point_s pos;
    float const_att;
    float linear_att;
    float quad_att;
    vector_s spotDir;
    float spotCutoff;
    float spotExp;
    color_s ambient;
    color_s diffuse;
};

typedef struct {
    matrix_s world;
    matrix_s view;
    matrix_s projection;
    matrix_s totalTransform;
    void updateTransform(){
        matrix_s m = view * world;
        totalTransform = projection * m;
    }
}transform_s;

//GLfloat amb_Diff[4] = { 0.1, 0.5, 0.8, 1.0 };
//GLfloat specular[4] = { 1, 1, 1, 1.0 };
//GLfloat globalAmbient[4] = {1,0.1,0.1,1.0};
//GLfloat shin[] = { 10 };

class Scene{
public:
    Scene(){
        lightN = 1;;
        objectsN = 1;
        objectArray = new Object[objectsN];
        globalAmbient = color_s(0.2, 0.2, 0.2, 1.0);
    }
    
    int lightN;
    Light light;
    int objectsN;
    Object *objectArray;
    color_s background;
    color_s globalAmbient;
    transform_s transform;
};

#endif /* _SCENE_H_ */
