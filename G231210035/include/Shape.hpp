#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Screen.hpp"   

class Shape {
protected:
    int x;      
    int y;      
    int height; 
    int width;  
    char ch;    
    int z;      

public:
    // Constructor
    Shape(int x, int y, int height, char ch, int z);

    // Virtual destructor
    virtual ~Shape();

    // Pure virtual draw function
    virtual void draw(Screen& screen) = 0;

    // Move shape in X,Y direction
    void move(int dx, int dy);

    // Resize → height değişir, width türemiş sınıfta hesaplanır
    virtual void resize(int newHeight);

    // Getters
    int getX() const;
    int getY() const;
    int getHeight() const;
    int getWidth() const;
    char getChar() const;
    int getZ() const;

    // Setters
    void setX(int newX);
    void setY(int newY);
    void setZ(int newZ);
};

#endif
