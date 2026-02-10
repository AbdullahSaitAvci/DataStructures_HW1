/**
* App.cpp
* Ana uygulama sınıfı. Kullanıcıdan giriş alır, şekil listelerini yönetir ve ekrana çizer.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "App.hpp"
#include "NoSuchElement.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>



#ifdef _WIN32
#include <conio.h>   // _getch için

#endif

using namespace std;

App::App() {
    srand((unsigned)time(nullptr));
}

void App::calistir()
{
    cout << "==== Shape List Application ====\n";
    cout << "1) Rastgele olustur (20 dugum)\n";
    cout << "2) Dosyadan oku\n";
    cout << "0) Cikis\n";
    cout << "Seciminiz: ";

    int choice;
    cin >> choice;

    if (choice == 0) {
        return;
    }
    else if (choice == 1) {
        initRandom();
    }
    else if (choice == 2) {
        string path;
        cout << "Dosya adi: ";
        cin >> path;
        if (!loadFromFile(path)) {
            cout << "Dosya okunamadi, program sonlandiriliyor.\n";
            return;
        }
    }
    else {
        cout << "Gecersiz secim, program sonlandiriliyor.\n";
        return;
    }

    // Ana liste menusu
    listMenu();

    // Çıkmadan önce kaydedelim
    string outPath = "output.txt";
    if (saveToFile(outPath)) {
        cout << "\nMevcut durum \"" << outPath << "\" dosyasina kaydedildi.\n";
    }
    else {
        cout << "\nDosyaya kayit basarisiz.\n";
    }
}

// -----------------------------------------------------
// RASTGELE OLUŞTURMA
// -----------------------------------------------------
void App::initRandom()
{
    dll.clear();  // varsa eskiyi temizle

    int layerCount = DEFAULT_LAYER_COUNT;

    for (int i = 0; i < layerCount; ++i) {
        LinkedList* layer = new LinkedList();
        dll.add(layer);

        int shapeCount = MIN_SHAPES + rand() % (MAX_SHAPES - MIN_SHAPES + 1);

        for (int j = 0; j < shapeCount; ++j) {

            int type = rand() % 3;      // 0:Triangle, 1:Rectangle, 2:Star
            int h    = 2 + rand() % 6;  // "height" parametresi

            const char chars[] = "^#*@+=%";
            char ch = chars[rand() % (sizeof(chars) - 1)];

            int z = rand() % 10;

            Shape* s = nullptr;

            if (type == 0) {
                s = new Triangle(0, 0, h, ch, z);
            }
            else if (type == 1) {
                s = new Rectangle(0, 0, h, ch, z);
            }
            else {
                s = new Star(0, 0, h, ch, z);
            }

            // --- GERÇEK GENİŞLİK / YÜKSEKLİK HESABI ---
            int w = s->getWidth();

            // Üçgen ve dikdörtgen: h satır
            // Star (diamond): 2*h - 1 satır
            int drawHeight;
            if (type == 2) {           // Star
                drawHeight = 2 * h - 1;
            }
            else {                     // Triangle, Rectangle
                drawHeight = h;
            }

            // Çok büyük şekilleri ele
            if (w <= 0 || drawHeight <= 0 ||
                w > Screen::COLS || drawHeight > Screen::ROWS) {
                delete s;
                continue;
            }

            // Solda panel için boşluk bırak (0..14 panel, 15..COLS-1 şekiller)
            int minX = 15;
            int maxX = Screen::COLS - w;

            if (maxX < minX) {
                delete s;
                continue;
            }

            int x = minX + rand() % (maxX - minX + 1);

            // Yukarı / aşağı taşmayı engelle
            int maxY = Screen::ROWS - drawHeight;
            if (maxY < 0) {
                delete s;
                continue;
            }

            int y = rand() % (maxY + 1);

            s->setX(x);
            s->setY(y);

            layer->add(s);
        }
    }
}

bool App::loadFromFile(const string& path)
{
    ifstream in(path.c_str());
    if (!in) {
        cout << "Dosya acilamadi: " << path << endl;
        return false;
    }

    // --- Eski tüm yapıyı temizle ---
    dll.clear();   // DoublyLinkedList içindeki tüm LinkedList ve Shape'leri delete eder

    int layerCount = 0;
    if (!(in >> layerCount)) {
        cout << "Dosya formati hatali (layerCount okunamadi).\n";
        return false;
    }

    // --- Yeni layer’ları oku ---
    for (int i = 0; i < layerCount; i++)
    {
        int shapeCount = 0;
        if (!(in >> shapeCount)) {
            cout << "Dosya formati hatali (shapeCount okunamadi).\n";
            return false;
        }

        LinkedList* layer = new LinkedList();

        // --- Şekilleri oku ---
        for (int j = 0; j < shapeCount; j++)
        {
            char typeChar;
            int  x, y, h, z;
            char ch;

            if (!(in >> typeChar >> x >> y >> h >> ch >> z)) {
                cout << "Dosya formati hatali (sekil satiri okunamadi).\n";
                delete layer;
                return false;
            }

            Shape* s = nullptr;

            switch (typeChar)
            {
            case 'T': s = new Triangle(x, y, h, ch, z); break;
            case 'R': s = new Rectangle(x, y, h, ch, z); break;
            case 'S': s = new Star(x, y, h, ch, z); break;

            default:
                cout << "Bilinmeyen sekil tipi: " << typeChar << endl;
                delete layer;
                return false;
            }

            layer->add(s);
        }

        dll.add(layer);
    }

    cout << "Dosyadan okuma tamamlandi: " << path << endl;
    return true;   
}



bool App::saveToFile(const string& path)
{
    ofstream out(path.c_str());
    if (!out) {
        cout << "Dosya olusturulamadi: " << path << endl;
        return false;
    }

    out << dll.Count() << endl;

    for (int i = 0; i < dll.Count(); ++i) {
        LinkedList* layer = dll.elementAt(i);
        int shapeCount = (layer != NULL) ? layer->size() : 0;
        out << shapeCount << endl;

        if (layer == NULL) continue;

        Iterator it = layer->iterator();
        while (it.hasNext()) {
            Shape* s = it.next();
            if (s == NULL) continue;

            char typeChar = 'T';
            if (dynamic_cast<Rectangle*>(s) != NULL) typeChar = 'R';
            else if (dynamic_cast<Star*>(s) != NULL) typeChar = 'S';

            out << typeChar << " "
                << s->getX()      << " "
                << s->getY()      << " "
                << s->getHeight() << " "
                << s->getChar()   << " "
                << s->getZ()      << endl;
        }
    }
    
    return true;   
}

// -----------------------------------------------------
// SADECE BELİRLİ BİR LİSTENİN ŞEKİLLERİNİ ÇİZ
// -----------------------------------------------------

void App::drawList(int index)
{
#ifdef _WIN32
    system("cls");
#else
    cout << "\x1B[2J\x1B[H";
#endif

    screen.clear();

    // Soldaki panel
    drawLeftPanel(index);

    LinkedList* layer = nullptr;
    try {
        layer = dll.elementAt(index);
    }
    catch (NoSuchElement& e) {
        cout << "\nHata: " << e.Message() << endl;
        return;    // liste yoksa ek çizime gerek yok
    }

    if (layer != nullptr) {
        Iterator it = layer->iterator();
        while (it.hasNext()) {
            Shape* s = it.next();
            if (s != nullptr) {
                s->draw(screen);
            }
        }
    }

    screen.draw();

    cout << "\nListe: " << (index + 1) << " / " << dll.Count();
    if (layer != nullptr) {
        cout << "   (sekil sayisi: " << layer->size() << ")";
    }
    cout << "\n(w/s) hareket  (f) listeyi sec  (c) sil  (q) cik : ";
}



void App::drawLeftPanel(int currentIndex)
{
    int count = dll.Count();
    if (count == 0) return;

    const int maxVisible = 6;     // ekranda en fazla 6 dugum
    const int boxWidth   = 9;     // "*********" genisligi

    // Hangi sayfada olduğumuzu bul
    int page       = currentIndex / maxVisible;          // 0,1,2,3...
    int startIndex = page * maxVisible;                  // bu sayfanin ilk dugumu
    int visible    = count - startIndex;
    if (visible > maxVisible) visible = maxVisible;      // 6'dan fazla gostermiyoruz

    // Her dugum icin 3 satir kullanacagiz:
    // baseRow:   *********
    // baseRow+1: *  n  *
    // baseRow+2: *********

    for (int i = 0; i < visible; ++i) {
        int nodeIndex = startIndex + i;     // gercek dugum indeksi
        int baseRow   = i * 4;              // her dugum icin 4 satir aralik (3 satir + 1 bos)

        if (baseRow + 2 >= Screen::ROWS) break;

        LinkedList* layer = dll.elementAt(nodeIndex);
        int shapeCount = 0;
        if (layer != nullptr) {
            shapeCount = layer->size();
        }

        // Bu dugum icin 3 satiri once temizle
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 15; ++c) {
                screen.setPixel(c, baseRow + r, ' ');
            }
        }

        // Ust ve alt kenarlar: "*********"
        for (int c = 0; c < boxWidth; ++c) {
            screen.setPixel(c, baseRow,     '*');
            screen.setPixel(c, baseRow + 2, '*');
        }

        // Orta satirin sol ve sag kenarlari
        screen.setPixel(0,          baseRow + 1, '*');
        screen.setPixel(boxWidth-1, baseRow + 1, '*');

        // Orta satirin icini bosluk yap
        for (int c = 1; c < boxWidth-1; ++c) {
            screen.setPixel(c, baseRow + 1, ' ');
        }

        // Kutu icine sekil sayisini ortalanmis sekilde yaz
        std::string text = std::to_string(shapeCount);
        int innerWidth   = boxWidth - 2;  // kenarlar haric
        int startCol     = 1 + (innerWidth - (int)text.length()) / 2;
        if (startCol < 1) startCol = 1;

        for (int k = 0; k < (int)text.length() && (startCol + k) < boxWidth-1; ++k) {
            screen.setPixel(startCol + k, baseRow + 1, text[k]);
        }

        // Eger bu dugum seciliyse, sagina 3 satirda ok "<--" ciz
        if (nodeIndex == currentIndex) {
            int arrowCol = boxWidth + 1;  // kutunun hemen sag tarafi

            for (int r = 0; r < 3; ++r) {
                screen.setPixel(arrowCol,     baseRow + r, '<');
                screen.setPixel(arrowCol + 1, baseRow + r, '-');
                screen.setPixel(arrowCol + 2, baseRow + r, '-');
            }
        }
    }
}

// -----------------------------------------------------
// LİSTE MENÜSÜ: W/S ile listenin içinde gezin, C ile liste sil
// -----------------------------------------------------

void App::listMenu()
{
    if (dll.Count() == 0) {
        cout << "Liste bos.\n";
        return;
    }

    int  current = 0;
    bool running = true;

    while (running && dll.Count() > 0)
    {
        // Seçili listeyi çiz
        drawList(current);

        char ch;
    #ifdef _WIN32
        ch = _getch();
        cout << ch << "\n";
    #else
        cin >> ch;
    #endif

        switch (ch)
        {
        case 'w': case 'W':
            if (current > 0) current--;
            break;

        case 's': case 'S':
            if (current < dll.Count() - 1) current++;
            break;

        case 'f': case 'F':
        {
            // Seçili listenin şekilleriyle oynanan alt menü
            int newIndex = shapeMenu(current);

            if (newIndex == -1) {
                // Bu listedeki tüm şekiller silinmiş ve liste de kaldırılmış
                if (dll.Count() == 0) {
                    running = false;      // Hiç liste kalmadı → çık
                }
                else {
                    // Eski index liste sayısını aşıyorsa son listeye git
                    if (current >= dll.Count())
                        current = dll.Count() - 1;
                }
            }
            else {
                // Liste hâlâ var, aynı veya farklı index geri gelebilir
                current = newIndex;
            }
            break;
        }

        case 'c': case 'C':
        {
        dll.removeAt(current);

        if (dll.Count() == 0) {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\x1B[2J\x1B[H";
    #endif
        running = false;   // listMenu'den çık
        }
    else if (current >= dll.Count()) {
        current = dll.Count() - 1;
    }
    break;
    }   

        }
    }
}

Shape* App::getShapeByIndex(LinkedList* layer, int index)
{
    if (layer == nullptr) return nullptr;
    if (index < 0) return nullptr;

    Iterator it = layer->iterator();
    int i = 0;
    Shape* s = nullptr;

    while (it.hasNext()) {
        s = it.next();
        if (i == index) return s;
        i++;
    }
    return nullptr;
}

int App::shapeMenu(int listIndex)
{
    // Başlangıç kontrolleri
    if (dll.Count() == 0) return -1;
    if (listIndex < 0 || listIndex >= dll.Count()) return -1;

    int  currentShape = 0;
    bool running      = true;

    while (running)
    {
        // ---- Her turda GÜNCEL düğümü al ----
        if (dll.Count() == 0) return -1;
        if (listIndex < 0 || listIndex >= dll.Count()) return -1;

        LinkedList* layer = dll.elementAt(listIndex);

// Bu listedeki şekiller başka yerden silinmişse:
// Listeyi kaldır ve LISTE MENÜSÜNE geri dön.
if (layer == nullptr || layer->size() == 0) {
    dll.removeAt(listIndex);

    if (dll.Count() == 0) {
        // Hiç liste kalmadı → listMenu bunu newIndex == -1 olarak anlayacak
        return -1;
    }

    if (listIndex >= dll.Count())
        listIndex = dll.Count() - 1;

    // Yeni current liste index’ini listMenu’ya bildir
    return listIndex;
}


        // ---------- ÇİZ ----------
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\x1B[2J\x1B[H";
    #endif

        screen.clear();

        // Sol panel
        drawLeftPanel(listIndex);

        // Bu listedeki TÜM şekilleri çiz
        Iterator itDraw = layer->iterator();
        while (itDraw.hasNext()) {
            Shape* s = itDraw.next();
            if (s != nullptr) {
                s->draw(screen);    // istersen buraya +LEFT_PANEL_WIDTH offset’i ekleyebilirsin
            }
        }

        screen.draw();

        // Alt menü
        cout << "\nListe: " << (listIndex + 1) << " / " << dll.Count()
             << "   (sekil sayisi: " << layer->size() << ")\n";
        cout << "(w/a/s/d) hareket  (q) onceki sekil  (e) sonraki sekil"
             << "  (c) sekil sil  (g) listeye don : ";

        char ch;
    #ifdef _WIN32
        ch = _getch();
        cout << ch << "\n";
    #else
        cin >> ch;
    #endif

        switch (ch)
        {
        // ===== HAREKET =====
        case 'w': case 'W':
        {
            Shape* s = getShapeByIndex(layer, currentShape);
            moveShape(s, 0, -1);
            break;
        }
        case 's': case 'S':
        {
            Shape* s = getShapeByIndex(layer, currentShape);
            moveShape(s, 0, +1);
            break;
        }
        case 'a': case 'A':
        {
            Shape* s = getShapeByIndex(layer, currentShape);
            moveShape(s, -1, 0);
            break;
        }
        case 'd': case 'D':
        {
            Shape* s = getShapeByIndex(layer, currentShape);
            moveShape(s, +1, 0);
            break;
        }

        // ===== ŞEKİL SEÇ =====
        case 'q': case 'Q':   // önceki şekil
            if (currentShape > 0)
                currentShape--;
            break;

        case 'e': case 'E':   // sonraki şekil
            if (currentShape < layer->size() - 1)
                currentShape++;
            break;

        // ===== ŞEKİL SİL =====
        case 'c': case 'C':
        {
        if (layer->size() == 0)
            break;

        // Seçili şekli sil
        layer->removeAt(currentShape);

        // Bu listede hiç şekil kalmadıysa → listeyi de sil
        if (layer->size() == 0)
        {
            dll.removeAt(listIndex);

        if (dll.Count() == 0) {
            // Hiç liste kalmadı → listMenu, newIndex == -1 görünce programdan çıkar
            return -1;
        }

        // Hâlâ liste varsa, index’i düzelt
        if (listIndex >= dll.Count())
            listIndex = dll.Count() - 1;

        // Artık bu shapeMenu bitiyor, LISTE MENÜSÜNE geri dönüyoruz
        return listIndex;
    }

    // Buraya geliyorsak listede hâlâ şekil var.
    // Sondaki şekli sildiysek index’i düzelt.
    if (currentShape >= layer->size())
        currentShape = layer->size() - 1;

    break;
}

    // ===== LİSTE MENÜSÜNE DÖN =====
    case 'g': case 'G':
        running = false;
        break;

        default:
            break;
        }
    }

    // Liste hâlâ duruyorsa, güncel index ile listMenu'ye dön
    return listIndex;
}

// -----------------------------------------------------
// TÜM ŞEKİLLERİ z'YE GÖRE ÇİZ 
// -----------------------------------------------------
void App::drawAll()
{
    int totalShapes = 0;
    int layerCount  = dll.Count();

    for (int i = 0; i < layerCount; ++i) {
        LinkedList* layer = dll.elementAt(i);
        if (layer != nullptr) {
            totalShapes += layer->size();
        }
    }

    if (totalShapes == 0) return;

    Shape** arr = new Shape*[totalShapes];
    int index = 0;

    for (int i = 0; i < layerCount; ++i) {
        LinkedList* layer = dll.elementAt(i);
        if (layer == nullptr) continue;

        Iterator it = layer->iterator();
        while (it.hasNext()) {
            Shape* s = it.next();
            if (s != nullptr) {
                arr[index++] = s;
            }
        }
    }

    int n = index;

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j]->getZ() < arr[minIdx]->getZ()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Shape* tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }

    screen.clear();
    for (int i = 0; i < n; ++i) {
        arr[i]->draw(screen);
    }
    screen.draw();

    delete[] arr;
}

void App::moveShape(Shape* s, int dx, int dy)
{
    if (s == nullptr) return;

    int hParam = s->getHeight();
    int w      = s->getWidth();

    // Star icin gercek cizim yuksekligi 2*h-1
    int drawH = hParam;
    if (dynamic_cast<Star*>(s) != nullptr) {
        drawH = 2 * hParam - 1;
    }

    int newX = s->getX() + dx;
    int newY = s->getY() + dy;

    // Solda panel icin bosluk: 0..14 panel, 15..COLS-1 sekiller
    int minX = 15;
    int maxX = Screen::COLS - w;

    int minY = 0;
    int maxY = Screen::ROWS - drawH;

    if (newX < minX) newX = minX;
    if (newX > maxX) newX = maxX;
    if (newY < minY) newY = minY;
    if (newY > maxY) newY = maxY;

    s->setX(newX);
    s->setY(newY);
}


