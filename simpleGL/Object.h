//
//  Object.h
//  simpleGL
//
//  Created by EBAO on 2017/6/9.
//  Copyright © 2017年 EBAO. All rights reserved.
//

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <stdio.h>
#include "ComponentDef.h"
#include "Bitmap.h"

typedef struct{
    color_s ambient;
    color_s diffuse;
    color_s specular;
    float shininess;
}material_s;

typedef struct Vector2f{
    Vector2f(){};
    Vector2f(float a,float b){
        x = a;
        y = b;
    }
    float x,y;
}vector2f_s;

typedef struct{
    int width() const{
        return bmp->width();
    };
    int height() const{
        return bmp->height();
    };
    tdogl::Bitmap *bmp;
    
    color_s getTexture(vector2f_s v){
        return getTexture(v.x, v.y);
    }
    
    color_s getTexture(float x,float y){
        int col = (int)(x * (width()- 1));
        int row = (int)(y * (height() - 1));
        
        unsigned char* ptr = bmp->getPixel(col,row);
        
        tdogl::Bitmap::Format format = bmp->format();

        float R,G,B,A;
        
        switch(format){
            case tdogl::Bitmap::Format_Grayscale:
                R = G = B = (float)*ptr/255.0;
                A = 1.0f;
                break;
            case tdogl::Bitmap::Format_GrayscaleAlpha:
                R = G = B = (float)*ptr/255.0;
                A = (float)*(ptr+1)/255.0;
                break;
            case tdogl::Bitmap::Format_RGB:
                R = (float)*ptr/255.0;
                G = (float)*(ptr+1)/255.0;
                B = (float)*(ptr+2)/255.0;
                A = 1.0f;
                break;
            case tdogl::Bitmap::Format_RGBA:
                R = (float)*ptr/255.0;
                G = (float)*(ptr+1)/255.0;
                B = (float)*(ptr+2)/255.0;
                A = (float)*(ptr+3)/255.0;
                break;
        }
        return color_s(R,G,B,A);
    }
}texture_s;

class Object{
public:
    Object(){
        triangleNum = 4;
        vertexArray = new point_s[12];
        
        vertexArray[0] = point_s(-0.5,0.5,-2.0,1.0);
        vertexArray[1] = point_s(0.5,-0.5,-2.0,1.0);
        vertexArray[2] = point_s(-0.5,-0.5,-2.0,1.0);
        
        vertexArray[3] = point_s(-0.5,0.5,-2.0,1.0);
        vertexArray[4] = point_s(0.5,0.5,-2.0,1.0);
        vertexArray[5] = point_s(0.5,-0.5,-2.0,1.0);
        
        vertexArray[6] = point_s(-0.5,0.5,-2.0,1.0);
        vertexArray[7] = point_s(-0.5,-0.5,-3.0,1.0);
        vertexArray[8] = point_s(-0.5,-0.5,-2.0,1.0);
        
        vertexArray[9] = point_s(-0.5,0.5,-2.0,1.0);
        vertexArray[10] = point_s(-0.5,-0.5,-3.0,1.0);
        vertexArray[11] = point_s(-0.5,0.5,-3.0,1.0);
        
        normalArray = new vector_s[12];
        
        for(int i = 0;i < 6;i++)
            normalArray[i] = point_s(0.0,0.0,1.0,1.0);
        
        for(int i = 6;i < 12;i++)
            normalArray[i] = point_s(-1.0,0.0,0.0,1.0);
        
        texCoord = new vector2f_s[12];
        texCoord[0] = vector2f_s(0,1);
        texCoord[1] = vector2f_s(1,0);
        texCoord[2] = vector2f_s(0,0);
        
        texCoord[3] = vector2f_s(0,1);
        texCoord[4] = vector2f_s(1,1);
        texCoord[5] = vector2f_s(1,0);
        
        texCoord[6] = vector2f_s(1,1);
        texCoord[7] = vector2f_s(0,0);
        texCoord[8] = vector2f_s(1,0);
        
        texCoord[9] = vector2f_s(1,1);
        texCoord[10] = vector2f_s(0,0);
        texCoord[11] = vector2f_s(0,1);
        
        material = new material_s;
        material->ambient = color_s(0.1, 0.5, 0.8, 1.0);
        material->diffuse = color_s(0.1, 0.5, 0.8, 1.0);
        material->specular = color_s(0.1, 0.5, 0.8, 1.0);
        material->shininess = 10;
        material->specular = color_s(1, 1, 1, 1.0);
        
        tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile("/Users/ebao/Desktop/49101E7D-D29C-4D08-A17D-B53E04853347.png");
        bmp.flipVertically();
        
        texture = new texture_s;
        texture->bmp = new tdogl::Bitmap(bmp);
        
        material->specular = color_s(1, 1, 1, 1.0);

    }
    
    int triangleNum;
    point_s *vertexArray;
    vector_s *normalArray;
    vector2f_s *texCoord;
    bool hasTexture;
    material_s *material;
    texture_s *texture;
};

#endif /* _OBJECT_H_ */
