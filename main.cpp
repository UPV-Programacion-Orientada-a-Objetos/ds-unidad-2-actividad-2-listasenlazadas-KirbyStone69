#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

int main(){
    std::cout << "Iniciando Decodificador PRT-7...\n";
    std::cout << R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠟⠃⠀⠀⠙⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠋⠀⠀⠀⠀⠀⠀⠘⣆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠾⢛⠒⠀⠀⠀⠀⠀⠀⠀⢸⡆⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣶⣄⡈⠓⢄⠠⡀⠀⠀⠀⣄⣷⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣷⠀⠈⠱⡄⠑⣌⠆⠀⠀⡜⢻⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡿⠳⡆⠐⢿⣆⠈⢿⠀⠀⡇⠘⡆⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣷⡇⠀⠀⠈⢆⠈⠆⢸⠀⠀⢣⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣧⠀⠀⠈⢂⠀⡇⠀⠀⢨⠓⣄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⣦⣤⠖⡏⡸⠀⣀⡴⠋⠀⠈⠢⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⠁⣹⣿⣿⣿⣷⣾⠽⠖⠊⢹⣀⠄⠀⠀⠀⠈⢣⡀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⣇⣰⢫⢻⢉⠉⠀⣿⡆⠀⠀⡸⡏⠀⠀⠀⠀⠀⠀⢇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢨⡇⡇⠈⢸⢸⢸⠀⠀⡇⡇⠀⠀⠁⠻⡄⡠⠂⠀⠀⠀⠘
⢤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠛⠓⡇⠀⠸⡆⢸⠀⢠⣿⠀⠀⠀⠀⣰⣿⣵⡆⠀⠀⠀⠀
⠈⢻⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡿⣦⣀⡇⠀⢧⡇⠀⠀⢺⡟⠀⠀⠀⢰⠉⣰⠟⠊⣠⠂⠀⡸
⠀⠀⢻⣿⣿⣷⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⢧⡙⠺⠿⡇⠀⠘⠇⠀⠀⢸⣧⠀⠀⢠⠃⣾⣌⠉⠩⠭⠍⣉⡇
⠀⠀⠀⠻⣿⣿⣿⣿⣿⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣞⣋⠀⠈⠀⡳⣧⠀⠀⠀⠀⠀⢸⡏⠀⠀⡞⢰⠉⠉⠉⠉⠉⠓⢻⠃
⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⢀⣀⠠⠤⣤⣤⠤⠞⠓⢠⠈⡆⠀⢣⣸⣾⠆⠀⠀⠀⠀⠀⢀⣀⡼⠁⡿⠈⣉⣉⣒⡒⠢⡼⠀
⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣎⣽⣶⣤⡶⢋⣤⠃⣠⡦⢀⡼⢦⣾⡤⠚⣟⣁⣀⣀⣀⣀⠀⣀⣈⣀⣠⣾⣅⠀⠑⠂⠤⠌⣩⡇⠀
⠀⠀⠀⠀⠀⠀⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡁⣺⢁⣞⣉⡴⠟⡀⠀⠀⠀⠁⠸⡅⠀⠈⢷⠈⠏⠙⠀⢹⡛⠀⢉⠀⠀⠀⣀⣀⣼⡇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⡟⢡⠖⣡⡴⠂⣀⣀⣀⣰⣁⣀⣀⣸⠀⠀⠀⠀⠈⠁⠀⠀⠈⠀⣠⠜⠋⣠⠁⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⡟⢿⣿⣿⣷⡟⢋⣥⣖⣉⠀⠈⢁⡀⠤⠚⠿⣷⡦⢀⣠⣀⠢⣄⣀⡠⠔⠋⠁⠀⣼⠃⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⡄⠈⠻⣿⣿⢿⣛⣩⠤⠒⠉⠁⠀⠀⠀⠀⠀⠉⠒⢤⡀⠉⠁⠀⠀⠀⠀⠀⢀⡿⠀⠀⠀
    )";
    std::cout << "Esperando tramas desde el ESP32...\n\n";

    int laputisimaesp32 = open("/dev/ttyUSB0", O_RDONLY | O_NOCTTY);
    /*
    las vanderas 
    O_RDONLY = solo abrir para lectura
    O_NOCTTY = le dice al sistema: “no conviertas este puerto en mi terminal principal”.
    Esto evita que, por error, el puerto capture entradas de teclado o señales como Ctrl+C.
    */

    if(laputisimaesp32 < 0){
        std::cerr << "Error: no se pudo abrir /dev/ttyUSB0";
        std::cout << R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠶⠛⠉⠀⠀⠀⠀⠉⠙⠶⠦⣀⡀⠀⠀⠀⣀⣠⠴⠶⠞⠛⠛⠶⠤⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠲⣞⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠞⠁⠀⠀⠀⠀⠀⣀⣠⡤⠤⠤⠤⣤⣄⡀⠀⠀⠹⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣴⠃⠀⠀⠀⠀⢠⠶⠛⠉⠁⠀⠀⠀⠀⠀⠈⠙⠓⠦⢤⣿⠤⠖⠒⠒⠒⠒⠒⠚⠒⠓⠲⠾⢧⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⡤⠤⠤⠤⠤⣭⣳⣤⡀⠀⠀⠀⢀⣀⣀⣠⣤⣤⣤⣬⣙⣳⣦⣄⠀⠀
⠀⠀⠀⠀⢀⣀⣿⣷⣦⣤⣄⣀⡀⠀⣀⣀⣤⣤⣤⣶⣯⣭⣥⣶⣶⣯⣭⣽⣶⣶⣬⣭⣙⣴⢖⣫⣭⣿⣿⣶⣶⣶⣶⣶⣾⣿⣿⣿⣷⣤
⠀⠀⠀⣤⠛⢹⡇⠈⠉⠙⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⡿⣿⣿⣿⣿
⠀⢀⡞⠁⠀⠸⠇⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡣⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿
⢀⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡁⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⡿⠛⠉⠉⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⣀⠀⠙⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⣉⣩⡭⠿⠛⠉⠁⠀⠀⠀⠀⠀⠙⠛⢿⡒⠛⠛⠛⠋⠻⡭⡉⠁⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠹⣦⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠛⠉⠉⠉⠳⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡄⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⢀⣀⠀⠀⠀⠉⠙⠳⠦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣇⡀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⡄⠀⠈⠉⠛⠢⢤⣤⣀⠀⠀⠈⠉⠉⠑⠒⠒⠒⠢⠤⢤⣤⣤⣤⣤⣄⣠⣤⣤⡤⠔⠚⠋⠁⢀⡇⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⢦⣄⡀⠀⠀⠀⠈⠉⠙⠓⠒⠦⢦⣤⣤⣄⣀⣀⣀⣀⣀⣀⠀⠀⠈⠁⠀⢀⣀⣀⣠⣤⠖⠉⠀⠀
⠛⣻⣶⣦⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠲⢤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠁⠀⠈⠀⠉⠀⠉⠉⠉⠉⠉⣉⣉⣤⣥⣷⠾⠓⢲⣚⡟
⠈⣞⣷⣴⣌⣽⣫⣿⠷⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠛⠛⠛⠷⠶⠶⠶⠶⢶⢦⣤⣤⣴⢿⣯⡉⠉⣁⣞⠗⢂⠹⡝⠅
⠀⣻⣿⣷⢪⣿⣋⠀⠀⢀⡈⣽⡛⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⣛⣍⣿⢷⡆⣈⣻⣮⠀⣻⣧⢿⣷⣶⠾
⠿⣿⣿⠾⠿⣿⡿⣵⣿⡏⣿⠹⣿⣞⢷⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣴⠟⡾⣿⣹⣿⣿⢷⡽⣏⠛⠓⠒⠛⠛⠛⠛⠛
⡼⢭⠥⣴⠬⣿⠿⢯⡿⢥⡿⢧⡿⢿⡿⢯⠭⢭⡿⢿⡿⢿⡿⢶⡶⢶⡾⢾⡿⢿⡭⢿⣿⠼⣧⠍⣭⠭⣥⠬⣷⢻⣆⣀⣦⣀⣴⣀⣀⠀
⢱⡿⠶⠿⠶⠾⠶⠾⠶⠾⠷⠾⠶⠾⠷⠾⠶⠾⠷⠾⠷⠾⠷⠾⠷⠾⠟⠛⠻⠞⠛⠛⠛⠛⠛⠛⠛⠋⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⢹⡀
⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇)"<< "\n";
        close(laputisimaesp32);
        return -1;//error criticamente critico
    }

    //el termios es una configuracion especial para terminales
    struct termios cpuerto;
    memset(&cpuerto, 0, sizeof cpuerto);

    if (tcgetattr(laputisimaesp32, &cpuerto) != 0) {
        std::cerr << "Error: no se pudo obtener atributos del puerto\n";
        close(laputisimaesp32);
        return 1;
    }
    cfsetispeed(&cpuerto, B9600);
    cfsetospeed(&cpuerto, B9600);

    cpuerto.c_cflag = (cpuerto.c_cflag & ~CSIZE) | CS8; // 8 bits
    cpuerto.c_iflag = IGNPAR; // Ignorar errores de paridad
    cpuerto.c_oflag = 0;
    cpuerto.c_lflag = 0; // Modo sin canon (lectura directa)
    cpuerto.c_cc[VMIN] = 0;  // Leer al menos 1 byte
    cpuerto.c_cc[VTIME] = 28; // 2.5
    tcsetattr(laputisimaesp32, TCSANOW, &cpuerto);

    tcsetattr(laputisimaesp32, TCSANOW, &cpuerto);
    std::cout << "Conexión establecida. Esperando Trabas...\n\n";

    ListaDeCarga miLista;
    RotorDeMapeo miRotor;

    char buffer[64];
    int pos = 0;
    char dato;
    while (true) {
        int n = read(laputisimaesp32, &dato, 1);
        if (n > 0) {
            if (dato == '\n' || dato == '\r') {
                if (pos > 0) {
                    buffer[pos] = '\0';
                    std::cout << "Trama recibida: [" << buffer << "] -> Procesando...\n";
                    
                    if (strcmp(buffer, "END") == 0) {
                        std::cout << "\n---\nFlujo de datos terminado.\nMENSAJE OCULTO ENSAMBLADO:\n";
                        miLista.imprimirMensaje();
                        std::cout << "---\nLiberando memoria... Sistema apagado.\n";
                        break;
                    }
                    
                    // PARSING MEJORADO
                    char tipo = buffer[0];
                    
                    if (strlen(buffer) < 3) {
                        std::cerr << "Trama muy corta: " << buffer << std::endl;
                        pos = 0;
                        continue;
                    }
                    
                    // Buscar la coma
                    char* coma = strchr(buffer, ',');
                    if (!coma) {
                        std::cerr << "No se encontró coma en: " << buffer << std::endl;
                        pos = 0;
                        continue;
                    }
                    
                    // El valor es todo lo que está después de la coma
                    const char* valor_ptr = coma + 1;
                    
                    TramaBase* trama = nullptr;
                    
                    if (tipo == 'L') {
                        char c;
                        // Si el valor está vacío o es solo un espacio, es un espacio
                        if (strlen(valor_ptr) == 0) {
                            c = ' ';
                        } else {
                            c = valor_ptr[0];
                        }
                        trama = new TramaLoad(c);
                        std::cout << "Trama L," << (c == ' ' ? "[space]" : std::string(1, c)) << " -> ";
                    } else if (tipo == 'M') {
                        int entero = atoi(valor_ptr);
                        trama = new TramaMap(entero);
                        std::cout << "Trama M," << entero << " -> ";
                    } else {
                        std::cerr << "Tipo de trama desconocido: " << tipo << std::endl;
                    }
                    
                    if (trama) {
                        trama->procesar(&miLista, &miRotor);
                        delete trama;
                    }
                    
                    pos = 0;
                }
            } else {
                if (pos < sizeof(buffer) - 1) {
                    buffer[pos++] = dato;
                } else {
                    // Buffer lleno, reiniciamos para evitar overflow
                    std::cerr << "Buffer overflow, limpiando buffer\n";
                    pos = 0;
                }
            }
        } else if (n == 0) {
            // Timeout: no llegaron datos en el tiempo especificado
            if (pos > 0) {
                buffer[pos] = '\0';
                std::cout << "Timeout alcanzado. Procesando trama acumulada: [" << buffer << "]\n";
                
                // Mismo parsing que arriba
                char tipo = buffer[0];
                
                if (strlen(buffer) < 3) {
                    std::cerr << "Trama muy corta: " << buffer << std::endl;
                    pos = 0;
                    continue;
                }
                
                char* coma = strchr(buffer, ',');
                if (!coma) {
                    std::cerr << "No se encontró coma en: " << buffer << std::endl;
                    pos = 0;
                    continue;
                }
                
                const char* valor_ptr = coma + 1;
                
                TramaBase* trama = nullptr;
                
                if (tipo == 'L') {
                    char c;
                    if (strlen(valor_ptr) == 0) {
                        c = ' ';
                    } else {
                        c = valor_ptr[0];
                    }
                    trama = new TramaLoad(c);
                    std::cout << "Trama L," << (c == ' ' ? "[space]" : std::string(1, c)) << " -> ";
                } else if (tipo == 'M') {
                    int entero = atoi(valor_ptr);
                    trama = new TramaMap(entero);
                    std::cout << "Trama M," << entero << " -> ";
                } else {
                    std::cerr << "Tipo de trama desconocido: " << tipo << std::endl;
                }
                
                if (trama) {
                    trama->procesar(&miLista, &miRotor);
                    delete trama;
                }
                
                pos = 0;
            }
        } else {
            std::cerr << "Error en lectura del puerto\n";
            break;
        }
    }
    
    
    close(laputisimaesp32);





    return 0;
}