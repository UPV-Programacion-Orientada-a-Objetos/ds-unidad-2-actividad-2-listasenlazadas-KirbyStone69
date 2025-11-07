// TramaBase.h
#pragma once//indica que entre solo una vez este archivo
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

class TramaBase {
public:
    //virtual para aceptar polimorfismo y ser editada con override en su hijo
    //ejemplo pal futuro 
    //void procesar() override {}
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0; // no hace nada, solo promete que existira 

    //se ejecuta al ser elimindado el objeto
    virtual ~TramaBase() {}
};
