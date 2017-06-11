//
//  SimpleMaterial.h
//  simpleGL
//
//  Created by EBAO on 2017/6/9.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#ifndef _SIMPLEMATERIAL_H_
#define _SIMPLEMATERIAL_H_

#include "ComponentDef.h"
#include <stdio.h>

typedef struct{
    color_s ambient;
    color_s diffuse;
    color_s specular;
    float shininess;
}material_s;

#endif /* _SIMPLEMATERIAL_H_ */
