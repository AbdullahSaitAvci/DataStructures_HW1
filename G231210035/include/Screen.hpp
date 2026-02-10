#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
using namespace std;

class Screen {
public:
    // Ekran boyutları
    static const int ROWS = 25;
    static const int COLS = 100;

private:
    char buffer[ROWS][COLS];

public:
    Screen();

    //Ekranı boşluk karakteri ile temizler
    void clear();

    //Verilen (x, y) koordinatına karakter yerleştirir
    void setPixel(int x, int y, char ch);

    //Buffer'ı ekrana çizer
    void draw() const;
};

#endif
