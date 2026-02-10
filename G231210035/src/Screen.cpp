/**
* Screen.cpp
* ASCII ekran (25x80) buffer yapısı. Tüm şekiller bu buffer üzerine çizilir. Ekranı temizleme,
* piksel işleme ve buffer’ı konsola basma işlemleri bu sınıfta yapılır.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Screen.hpp"

Screen::Screen() {
    clear();
}

void Screen::clear() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            buffer[r][c] = ' ';
        }
    }
}

void Screen::setPixel(int x, int y, char ch) {
    // Sınır kontrolü – ekran dışına taşmasın
    if (x < 0 || x >= COLS) return;
    if (y < 0 || y >= ROWS) return;

    buffer[y][x] = ch;
}

void Screen::draw() const {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            cout << buffer[r][c];
        }
        cout << '\n';
    }
}
