#pragma once
#include "TramaBase.h"

class TramaLoad : public TramaBase {
    char dato;
public:
    TramaLoad(char d) : dato(d) {}
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};
