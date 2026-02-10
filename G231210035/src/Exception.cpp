/**
* Exception.cpp
* Özel durum (Exception) sınıfı. Hata mesajını tutar ve döndürür.
* Bilgisayar Mühendisliği 3. Sınıf (2/A)
* 1. Ödev 
* 23.11.2025
* Abdullah Sait AVCI
*/

#include "Exception.hpp"

string Exception::Message() const {
    return message;
}
