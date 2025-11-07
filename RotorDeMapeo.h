#pragma once //indica que entre solo una vez este archivo
#include <iostream>

struct NodoRotor{
    char letra;//hola
    NodoRotor* prev;
    NodoRotor* next;
};

class RotorDeMapeo{
NodoRotor* head;
public:
    RotorDeMapeo();
    ~RotorDeMapeo();

    void rotar(int n);
    char getMapeo(char in);
};
