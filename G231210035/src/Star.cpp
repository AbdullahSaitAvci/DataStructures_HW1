/**
* Star.cpp
* Yıldız (eşkenar dörtgen) görünümündeki şeklin oluşturulması. Height parametresine göre
* 2*h - 1 satır yüksekliğinde bir ASCII diamond çizimi yapılır.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Star.hpp"

Star::Star(int x, int y, int height, char ch, int z)
    : Shape(x, y, height, ch, z)
{
    if (this->height < 1)
        this->height = 1;

    
    width = 2 * this->height - 1;
}

void Star::resize(int newHeight)
{
    if (newHeight < 1)
        newHeight = 1;

    height = newHeight;
    width  = 2 * height - 1;
}

// Dolgu diamond cizimi
void Star::draw(Screen& screen)
{
    int h = height;
    if (h < 1) return;

    int totalRows = 2 * h - 1;      // ustten alta toplam satir
    int midX      = x + h - 1;      // ortadaki sutun

    for (int row = 0; row < totalRows; ++row) {
        int offset;
        if (row < h) {
            // üst yarı (0..h-1)
            offset = row;
        } else {
            // alt yarı (h..2h-2)
            offset = totalRows - 1 - row;
        }

        int startX   = midX - offset;
        int endX     = midX + offset;
        int currentY = y + row;

        for (int col = startX; col <= endX; ++col) {
            screen.setPixel(col, currentY, ch);
        }
    }
}
