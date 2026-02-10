/**
* Triangle.cpp
* Üçgen şeklinin çizim mantığını içeren sınıf. Shape sınıfından türemiştir ve draw()
* fonksiyonunda üçgen ASCII geometrisi oluşturulur.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Triangle.hpp"
#include "Screen.hpp"

//Üçgen kurucusu
Triangle::Triangle(int x, int y, int height, char ch, int z)
    : Shape(x, y, height, ch, z)
{
    //Burada width'i height'e göre hesaplıyoruz.
    //Tabanın genişliğini (width) 2*height - 1 alıyorum.
    width = 2 * height - 1;
}

//Üçgeni ekrana çiz
void Triangle::draw(Screen& screen) {
    //y: üst noktanın olduğu satır
    //x: tepe noktasının orta sütunu
    //height kadar satır aşağı iniyoruz.
    for (int row = 0; row < height; ++row) {
        int currentY = y + row;

        //Her satırda soldan ve sağdan içeri doğru gidiyoruz
        int startX = x - row;
        int endX   = x + row;

        for (int col = startX; col <= endX; ++col) {
            screen.setPixel(col, currentY, ch);
        }
    }
}

//Yüksekliği değiştirince width'i de yeniden hesapla
void Triangle::resize(int newHeight) {
    //Temel sınıftaki height'i güncelle
    Shape::resize(newHeight);

    //Üçgen için taban genişliğini yeni height'e göre tekrar hesaplıyoruz
    width = 2 * height - 1;
}
