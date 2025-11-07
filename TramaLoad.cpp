#include "TramaLoad.h"
#include <iostream>

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char decod = rotor->getMapeo(dato);
    carga->insertarAlFinal(decod);
    std::cout << "Fragmento '" << dato << "' decodificado como '" << decod << "'. Mensaje: ";
    carga->imprimirMensaje();
}