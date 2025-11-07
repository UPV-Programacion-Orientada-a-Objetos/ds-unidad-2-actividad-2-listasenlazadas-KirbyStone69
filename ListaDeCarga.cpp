#include "ListaDeCarga.h"

ListaDeCarga::~ListaDeCarga() {
    NodoCarga* aux = head;
    while (aux) {
        NodoCarga* sig = aux->next;
        delete aux;
        aux = sig;
    }
    head = nullptr;
    tail = nullptr;
}

void ListaDeCarga::insertarAlFinal(char c) {
    NodoCarga* nuevo = new NodoCarga{c, tail, nullptr};
    if (!head) {
        head = nuevo;
    } else {
        tail->next = nuevo;
    }
    tail = nuevo;
}

void ListaDeCarga::imprimirMensaje() {
    NodoCarga* aux = head;
    while (aux) {
        std::cout << aux->dato;
        aux = aux->next;
    }
    std::cout << std::endl;
}
