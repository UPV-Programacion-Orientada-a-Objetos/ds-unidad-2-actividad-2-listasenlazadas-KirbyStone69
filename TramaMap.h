#pragma once
#include "TramaBase.h"

class TramaMap : public TramaBase {
    int desplazamiento;
public:
    TramaMap(int n) : desplazamiento(n) {}
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};
