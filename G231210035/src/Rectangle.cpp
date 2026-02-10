/**
* Rectangle.cpp
* Dikdörtgen şeklinin ASCII ekran üzerinde çizilmesini sağlayan sınıf. Genişlik ve
* yükseklik hesaplamaları Shape temel sınıfını kullanır.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Rectangle.hpp"
#include "Screen.hpp"

Rectangle::Rectangle(int x, int y, int h, char ch, int z)
    : Shape(x, y, h, ch, z)
{
    //Burada width'i doğrudan height'in 2 katı yapıyorum.
    width = height * 2;
}

void Rectangle::draw(Screen& screen) {
    //height kadar satır, width kadar sütun çizeceğim.
    //(x, y) sol üst köşe olacak şekilde ilerliyor.
    for (int satir = 0; satir < height; ++satir) {
        int sy = y + satir;
        for (int sutun = 0; sutun < width; ++sutun) {
            int sx = x + sutun;
            screen.setPixel(sx, sy, ch);
        }
    }
}

void Rectangle::resize(int yeniH) {
    //Temel sınıftaki yükseklik güncellemesini çağırıyoruz.
    Shape::resize(yeniH);

    //Dikdörtgen için genişlik yeniden ayarlanmalı
    width = height * 2;
}
