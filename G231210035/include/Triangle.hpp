#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

//Shape sınıfından türeyen basit bir üçgen sınıfı
class Triangle : public Shape {
public:
    //Kullanıcı sadece height giriyor, width içeride hesaplanacak
    Triangle(int x, int y, int height, char ch, int z);

    //Üçgeni ekrana çizen fonksiyon
    virtual void draw(Screen& screen) override;

    //Yükseklik değişince üçgenin taban genişliği de değişmeli
    virtual void resize(int newHeight) override;
};

#endif 