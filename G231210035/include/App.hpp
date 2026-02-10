#ifndef APP_HPP
#define APP_HPP

#include <string>
using namespace std;

#include "Screen.hpp"
#include "DoublyLinkedList.hpp"
#include "LinkedList.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Star.hpp"

class App {
private:
    Screen screen;          // ASCII ekran
    DoublyLinkedList dll;   // Ana çift yönlü liste (her DNode'da LinkedList*)

    // Ödev: default 20 düğümlü çift yönlü liste
    static const int DEFAULT_LAYER_COUNT = 20;
    static const int MIN_SHAPES = 2;
    static const int MAX_SHAPES = 7;
    static const int LEFT_PANEL_WIDTH = 14;  // Panel + ok + boşluk


    // Yardımcı fonksiyonlar
    void initRandom();                      // Rastgele ana liste + şekiller üret
    bool loadFromFile(const string& path);  // Dosyadan yükle
    bool saveToFile(const string& path);    // Dosyaya kaydet

    void drawAll();                         // (İleride tümünü birden çizmek için)
    void drawList(int index);               // Sadece seçilen listenin şekillerini çiz
    void drawLeftPanel(int currentIndex); // Sol paneli çiz
    Shape* getShapeByIndex(LinkedList* layer, int index); // iterator ile sekil bul


    void listMenu();                        // W/S ile listeler arasında gezinme
    int  shapeMenu(int listIndex);          // secili listenin sekilleriyle oynanan alt menu
    void moveShape(Shape* s, int dx, int dy); // bir sekli dx,dy kadar kaydir (sinir kontrolu ile)
    

public:
    App();
    void calistir();                        // Program giriş noktası
};

#endif
