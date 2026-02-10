#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

//Basit dikdörtgen sınıfı (Shape'den türetilmiş)
class Rectangle : public Shape {
public:
    //Kullanıcı yine sadece yükseklik giriyor
    Rectangle(int x, int y, int h, char ch, int z);

    //Dikdörtgeni ekrana çizer
    virtual void draw(Screen& screen) override;

    //Yükseklik değişince genişlik de buna göre güncellenir
    virtual void resize(int yeniH) override;
};

#endif
