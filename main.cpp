#include <graphics.h>
#include <conio.h>
#include <iostream>
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Cuenta.hpp"
using namespace std;



class Sistema {
private:
    int windowWidth, windowHeight;
    int x, y;
    int userIndex, passIndex;
    char usuario[19];
    char contrasena[19];
    bool oculto;

    // Método para limpiar el buffer de teclado
    void limpiarBufferTeclado() {
        while (kbhit()) {
            getch();
        }
    }

    // Función para verificar si un clic está dentro de un rectángulo
    bool clicEnRectangulo(int left, int top, int right, int bottom, int x, int y) {
        return (x >= left && x <= right && y >= top && y <= bottom);
    }

    // Método para escribir en un campo
    void escribirEnCampo(int left, int top, int right, int bottom, char* texto, int maxLength, int &i, bool oculto) 
    {
        char letra;
        char pass = '*';
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 4);

        while (true) {
            if (kbhit()) {
                letra = getch();

                if (letra == '\r') {
                    texto[i] = '\0';
                    break;
                }

                if (letra == '\b' && texto[0] != '\0') {
                    texto[--i] = '\0';
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(left + 60, top + 10, right - 10, bottom - 10);
                    if (!oculto) {
                        outtextxy(left + 60, top + 20, texto);
                    } else {
                        char pass_text[19];
                        for (int j = 0; j < i; j++) {
                            pass_text[j] = pass;
                        }
                        pass_text[i] = '\0';
                        outtextxy(left + 60, top + 20, pass_text);
                    }
                }

                if (letra >= 32 && letra <= 126 && i < maxLength - 1) {
                    texto[i++] = letra;
                    texto[i] = '\0';
                    if (!oculto) {
                        outtextxy(left + 60, top + 20, texto);
                    } else {
                        char pass_text[19];
                        for (int j = 0; j < i; j++) {
                            pass_text[j] = pass;
                        }
                        pass_text[i] = '\0';
                        outtextxy(left + 60, top + 20, pass_text);
                    }
                }
                delay(5);
            } else if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (!clicEnRectangulo(left, top, right, bottom, x, y)) {
                    break;
                }
            }
            delay(5);
        }
    }

    // Método para mostrar la interfaz de login
    void LoginInterfaz() {
        readimagefile("payLogin.jpg", 0, 0, windowWidth, windowHeight);
    }

    void panelUsuario() {
        readimagefile("panelUser.jpg", 0, 0, windowWidth, windowHeight);

    }

    void panelAdmin() {
        readimagefile("panelUser.jpg", 0, 0, windowWidth, windowHeight);

    }

    // Método para manejar los clics en la interfaz de login
    int manejarClickLogin() {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 4);
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                limpiarBufferTeclado();
            }

            // Campo Usuario
            if (clicEnRectangulo(820, 203, 1380, 272, x, y)) {
                oculto = false;
                escribirEnCampo(820, 203, 1380, 272, usuario, 19, userIndex, oculto);
            }

            // Campo Contraseña
            if (clicEnRectangulo(820, 362, 1380, 431, x, y)) {
                oculto = true;
                escribirEnCampo(820, 362, 1380, 431, contrasena, 18, passIndex, oculto);
            }

            // Campo Iniciar Sesión
            if (clicEnRectangulo(1030, 475, 1143, 580, x, y)) {
                int codigo=0;
                if (Usuario::verificarLogin(usuario, contrasena, codigo)) {
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(870, 605 - 16, 870 + 500, 640);
                    cleardevice();
                    return codigo;

                } else {
                    outtextxy(870, 605, (char*)"Credenciales incorrectas");
                    delay(1000); 

                }
            }

            delay(10);
        }
        cout << usuario << " " << contrasena;
    }


public:
    Sistema(int width, int height) : windowWidth(width), windowHeight(height) {
        x = 0; y = 0;
        userIndex = 0; passIndex = 0;
        oculto = false;
        usuario[0] = '\0';
        contrasena[0] = '\0';
    }

    // Método para iniciar el sistema
    void iniciarSistema() {
        int gd = DETECT, gm;
        initgraph(&gd, &gm, (char*)"");
        initwindow(windowWidth, windowHeight, "UGMA PAY", 100, 100);
        int codigo;

        LoginInterfaz();
        codigo=manejarClickLogin();
        cleardevice();
        if(codigo!=30737409)
        {
            panelUsuario();
            Cliente cliente = Cliente::cargarCliente(codigo);
            cliente.mostrarCliente();
            Cuenta::cargarCuentas(codigo);
        }else
        {

        }
        while (true) {
            if (kbhit()) {
                char tecla = getch();
                if (tecla == 27) {  
                    break;  
                }
            }
            delay(10); 
        }
        closegraph();
    }
};



int main() {

    Sistema ugmaPay(1500, 750);  
    ugmaPay.iniciarSistema();   
    return 0;
}