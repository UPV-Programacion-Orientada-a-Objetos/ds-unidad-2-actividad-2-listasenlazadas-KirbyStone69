#pragma once //indica que entre solo una vez este archivo
#include <iostream>//quitar luego

struct NodoCarga{
    char dato;
    NodoCarga* prev;
    NodoCarga* next;
};

class ListaDeCarga{
    NodoCarga* head;
    NodoCarga* tail;
public:
    ListaDeCarga() : head(nullptr), tail(nullptr){}
    ~ListaDeCarga();
    void insertarAlFinal(char c);
    void imprimirMensaje();
};
