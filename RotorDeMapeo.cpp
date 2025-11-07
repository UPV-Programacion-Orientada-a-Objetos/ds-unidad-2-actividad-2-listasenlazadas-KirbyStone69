#include "RotorDeMapeo.h"

RotorDeMapeo::RotorDeMapeo() {
    NodoRotor* anterior = nullptr;
    head = nullptr;
    for(char c = 'A'; c <= 'Z' ; c++){
        NodoRotor* nuevo = new NodoRotor{c, anterior, nullptr};
        if (!head) head = nuevo;
        if(anterior) anterior->next = nuevo;
        anterior = nuevo;
    }
    // Cierra el círculo
    anterior->next = head;
    head->prev = anterior;
}

RotorDeMapeo::~RotorDeMapeo(){
    if (!head) return;
    
    NodoRotor* aux = head->next;
    while (aux != head) {
        NodoRotor* sig = aux->next;
        delete aux;
        aux = sig;
    }
    delete head;
    head = nullptr;
}

void RotorDeMapeo::rotar(int n) {
    if (n == 0 || !head) return;
    
    // Normalizar n para que sea positivo y menor que 26
    n = ((n % 26) + 26) % 26;
    
    // Rotar n posiciones
    for (int i = 0; i < n; i++) {
        head = head->next;
    }
}

char RotorDeMapeo::getMapeo(char in) {
    // Caso especial para espacio
    if (in == ' ') return ' ';
    if (!head) return in;
    // Implementación: mapeo tipo César según la rotación actual del rotor.
    // Calculamos el índice del caracter de entrada (0-25), y sumamos el
    // desplazamiento actual del head (head->letra - 'A'). Devolvemos la
    // letra resultante.
    if (in < 'A' || in > 'Z') return in; // fuera del alfabeto

    int idxIn = in - 'A';
    int headOffset = head->letra - 'A';
    int mapped = (idxIn + headOffset) % 26;
    return static_cast<char>('A' + mapped);
}