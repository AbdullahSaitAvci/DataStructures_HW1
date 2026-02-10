/**
* Shape.cpp
* Soyut Shape sınıfına ait ortak kurucu, hareket ettirme ve boyut güncelleme işlemleri.
* Türetilmiş sınıflar kendi draw() fonksiyonlarını override eder.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/


#include "Shape.hpp"

// Constructor
Shape::Shape(int x, int y, int height, char ch, int z)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->ch = ch;
    this->z = z;

    // Width base class'ta hesaplanmaz
    width = 0;
}

// Virtual destructor
Shape::~Shape() { }

// Move shape
void Shape::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

// Resize shape (width adjust derived class)
void Shape::resize(int newHeight)
{
    height = newHeight;
}

int Shape::getX() const { return x; }
int Shape::getY() const { return y; }
int Shape::getHeight() const { return height; }
int Shape::getWidth() const { return width; }
char Shape::getChar() const { return ch; }
int Shape::getZ() const { return z; }

void Shape::setX(int newX) { x = newX; }
void Shape::setY(int newY) { y = newY; }
void Shape::setZ(int newZ) { z = newZ; }
