#include <graphics.h>
#include <conio.h>
#include <iostream>
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Cuenta.hpp"

using namespace std;


enum Menu { TABLERO, TRANSFERENCIAS, DEPOSITOS, RETIROS, TRANSACCIONES, PAGOS, PERFIL, CERRAR_SESION };

class Sistema {
private:
    int windowWidth, windowHeight;
    int x, y;
    int userIndex, passIndex;
    char usuario[19];
    char contrasena[19];
    bool oculto;
    Menu menu;
    bool enSubmenu; 
    Cliente cliente;
    Cuenta cuentas[2];

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

    void transferenciasUI()
    {
        readimagefile("operaciones.jpg",0,0,1500,750);
    }

    void transaccionesUI()
    {
        readimagefile("transacciones.jpg",0,0,1500,750);
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
                    delay(1000); 

                }
            }

            delay(10);
        }
    }

    void manejarMenu()
    {

            //Opcion tablero
            if (clicEnRectangulo(30, 119, 250, 166, x, y)) {menu= TABLERO;}

           // Opción Trnasferencias
            if (clicEnRectangulo(30, 190, 260, 240, x, y)) {menu = TRANSFERENCIAS;}

            // Opción DEPOSITOS
            if (clicEnRectangulo(30, 245, 265, 300, x, y)) {menu = DEPOSITOS;}

            // Opción retiros
            if (clicEnRectangulo(30, 325, 250, 374, x, y)) {menu = RETIROS;}

            // Opción TRANSACCIONES
            if (clicEnRectangulo(30, 405, 265, 449, x, y)) {menu= TRANSACCIONES;}

            //PAGOS
            if (clicEnRectangulo(30, 480, 250, 530, x, y)) {menu= PAGOS;}

            //PERFIL
            if (clicEnRectangulo(30, 480, 250, 530, x, y)) {menu= PERFIL;}

            // Opción CERRAR SESION 
            if (clicEnRectangulo(30, 670, 250, 730, x, y)) {menu= CERRAR_SESION;}

            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
            }
    }
  
void manejarClickOperaciones() {
    int numero;
    char strNumero[100];
    
        settextstyle(8,0,5);
        setcolor(BLACK);
        setbkcolor(COLOR(0xc5,0xc9,0xe1));

        while(true)
        {

            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
            
            
                // Opción corriente
            if (clicEnRectangulo(615, 60, 680, 113, x, y)) {
                
                setfillstyle(SOLID_FILL, WHITE);
                numero = cuentas[1].seleccionarCuenta();
                itoa(numero, strNumero, 10);
                outtextxy(400, 380, strNumero);
                delay(50); 
            }

                // Opción Ahorro
            if (clicEnRectangulo(1043, 63,1098, 113, x, y)) {
                
                numero = cuentas[0].seleccionarCuenta();
                itoa(numero, strNumero, 10);
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(COLOR(0xc5,0xc9,0xe1));
                outtextxy(400, 380, strNumero);
                delay(50); 
            }

            if(clicEnRectangulo(0,0,290,750,x,y)){return;}
            }
            delay(100);
        }

    delay(10);  
}
    

    void dibujarMenu(int codigo, Menu &estado)
    {
        if (estado!=menu) 
        {
            cliente = Cliente::cargarCliente(codigo);

            Cuenta::cargarCuentas(codigo, cuentas);
            

            switch (menu) 
            {
                case TABLERO:
                    panelUsuario();
                    cliente.mostrarCliente();
                    mostrarCuentas();                 
                    
                    break;
                case TRANSFERENCIAS:  
                    transferenciasUI();
                    mostrarCuentas();
                    manejarClickOperaciones();
                    break;
                case TRANSACCIONES:
                    transaccionesUI();
                    mostrarCuentas();
                    break;
                case PAGOS:
                    break;
                case PERFIL:
                    break;
                case CERRAR_SESION:
                    break;  
            }
            estado = menu;
        }
    }

    void mostrarCuentas()
    {
        for (int i = 0; i < 2; i++) 
            {
                cuentas[i].mostrarCuenta(i); 
            }
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
            menu=TABLERO;
            panelUsuario();
            cliente = Cliente::cargarCliente(codigo);
            cliente.mostrarCliente();

            Cuenta::cargarCuentas(codigo,cuentas);
            mostrarCuentas();
        }else
        {

        }

        while(menu!=CERRAR_SESION)
        {
            Menu estado = menu;
            manejarMenu();
            dibujarMenu(codigo, estado);
            delay(5);
        }
        
        closegraph();
    }
};



int main() {

    Sistema ugmaPay(1500, 750);  
    ugmaPay.iniciarSistema();   
    return 0;
}