#ifndef STAR_HPP
#define STAR_HPP

#include "Shape.hpp"
#include "Screen.hpp"


class Star : public Shape {
public:
    // x, y : sol-üst köşe (üst ucun satırı y, orta sütun x + height - 1 gibi dusunebiliriz)
    // height : yarı yukseklik (üstten ortaya kadar olan satır sayısı)
    // ch : cizim karakteri
    // z : cizim onceligi
    Star(int x, int y, int height, char ch, int z);

    virtual void draw(Screen& screen) override;
    virtual void resize(int newHeight) override;
};

#endif
