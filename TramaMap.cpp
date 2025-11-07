#include "TramaMap.h"
#include <iostream>

void TramaMap::procesar(ListaDeCarga*, RotorDeMapeo* rotor) {
    rotor->rotar(desplazamiento);
    std::cout << "ROTANDO ROTOR " << 
        ((desplazamiento >= 0) ? "+" : "") << desplazamiento << 
        ". (Ahora 'A' se mapea a '" << rotor->getMapeo('A') << "')" << std::endl;
}