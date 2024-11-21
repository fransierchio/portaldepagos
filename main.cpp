#include <graphics.h>
#include <conio.h>
#include <iostream>
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "Transaccion.hpp"

using namespace std;


enum Menu { TABLERO, TRANSFERENCIAS, DEPOSITOS, RETIROS, PERFIL, CERRAR_SESION };

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

int filtrarYConvertirChar(const char* input) {
    char numeros[100] = "";
    int j = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (isdigit(input[i])) { 
            numeros[j++] = input[i];
        }
    }

    numeros[j] = '\0'; 

    if (strlen(numeros) > 0) {
        return atoi(numeros); 
    } else {
        return 0; 
    }
}

double convertirMontoValido(const char* monto) {
    string montoLimpiado = "";
    bool puntoDecimalEncontrado = false;

    for (int i = 0; monto[i] != '\0'; i++) {
        if (isdigit(monto[i])) {
            montoLimpiado += monto[i]; 
        } else if (monto[i] == '.' || monto[i] == ',') {
            if (!puntoDecimalEncontrado) {
                montoLimpiado += '.';  // Reemplazar la coma por punto, PARA EVITAR ERRORES
                puntoDecimalEncontrado = true; 
            } else {
                cout << "Monto inválido. Solo se permite un punto decimal." << endl;
                return 0.0;  // Si ya se encontró un punto, es inválido
            }
        } else {
            cout << "Monto no valido" << endl;
            return 0.0;  // Si contiene letras y simbolos, es inválido
        }
    }

    double montoFinal = atof(montoLimpiado.c_str());

    if (montoFinal <= 0) {
        cout << "Monto inválido. El monto debe ser mayor que cero." << endl;
        return 0.0;  // Retorna 0.0 si el monto no es válido
    }

    return montoFinal;
}

void limpiarChar(char* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = '\0';
    }
}

void limpiarReceptor() {
    setfillstyle(SOLID_FILL, COLOR(0x33, 0x33, 0x33));
    // Limpiar el área del nombre
    bar(1170, 290, 1457, 330);
    // Limpiar el área del teléfono
    bar(1170, 480, 1452, 520);
    // Limpiar el área del correo 
    bar(1170, 380, 1457, 423);
    // Limpiar el área del icono
    bar(1214, 66, 1397, 220);
    setbkcolor(COLOR(0x33, 0x33, 0x33));  
    setcolor(WHITE);
    settextstyle(8, 0, 1);
    outtextxy(1170,290, (char*)"USUARIO NO ENCONTRADO");
}

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

    void depositosUI()
        {
            readimagefile("depositoUI.jpg",0,0,1500,750);
        }

    void retirosUI()
        {
            readimagefile("RetirosUI.jpg",0,0,1500,750);
        }

    void perfilUI()
    {
        readimagefile("Perfil.jpg",0,0,1500,750);
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
                    bar(870, 605 - 16, 870 + 800, 640);
                    cleardevice();
                    return codigo;

                } else {
                    delay(1000); 
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(870, 605 - 16, 870 + 600, 640);

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
            if (clicEnRectangulo(30, 256, 265, 304, x, y)) {menu = DEPOSITOS;}

            // Opción retiros
            if (clicEnRectangulo(30, 325, 250, 374, x, y)) {menu = RETIROS;}

            //PERFIL
            if (clicEnRectangulo(30, 400, 250, 450, x, y)) {menu= PERFIL;}

            // Opción CERRAR SESION 
            if (clicEnRectangulo(30, 670, 250, 730, x, y)) {menu= CERRAR_SESION;}

            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X="<<x<<" Y="<<y;
            }
    }
  
    bool manejarClickOperaciones() {
    int numero=0;
    int receptorIndex=0,montoIndex=0, numReceptor=0, indexCuenta=-1;
    char receptor[19];
    char monto[19];
    int codigoReceptor;
    char strNumero[100];
    double montoTransferir=0;
    Cliente Recep;
    Cuenta RECEPCION;
    Cuenta EMISOR;;
    
    
        settextstyle(8,0,5);
        setcolor(BLACK);
        setbkcolor(WHITE);

        while(true)
        {
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                limpiarBufferTeclado();
                getmouseclick(WM_LBUTTONDOWN, x, y);
                
            
                // Opción corriente
            if (clicEnRectangulo(615, 60, 680, 113, x, y)) {
                
                setfillstyle(SOLID_FILL, WHITE);
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(WHITE);
                numero = cuentas[1].getNumeroCuenta();
                EMISOR = cuentas[1];
                indexCuenta=1;
                itoa(numero, strNumero, 10);
                outtextxy(400, 380, strNumero);
                delay(50); 
            }

                // Opción Ahorro
            if (clicEnRectangulo(1043, 63,1098, 113, x, y)) {
                numero = cuentas[0].getNumeroCuenta();
                EMISOR = cuentas[0];
                itoa(numero, strNumero, 10);
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(WHITE);
                outtextxy(400, 380, strNumero);
                delay(50); 
            }

            //receptor
            if(clicEnRectangulo(398, 521,1003, 596, x, y))
            {
                escribirEnCampo(370, 521,1003, 596, receptor, 10, receptorIndex,0);
                numReceptor = filtrarYConvertirChar(receptor);
                codigoReceptor=Cuenta::buscarCodigo(numReceptor);
                if(codigoReceptor!=0)
                {
                    RECEPCION = Cuenta::cargarCuenta(codigoReceptor, numReceptor);
                    setfillstyle(SOLID_FILL, COLOR(0x33, 0x33, 0x33));
                    bar(1170, 290, 1457, 330);
                    Recep = Cliente::cargarCliente(codigoReceptor);
                    Recep.mostrarReceptor();
                } else 
                { 
                    limpiarReceptor();
                }
            }
            //monto
            if(clicEnRectangulo(1101, 616,1455, 690, x, y))
            {
                escribirEnCampo(1070, 616,1455, 690, monto, 10, montoIndex,0);
                montoTransferir = convertirMontoValido(monto);
                if(montoTransferir==0.0)
                {
                    settextstyle(8,0,1);
                    setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
                    outtextxy(1222,570,(char*)"Monto  Invalido");
                    delay(1000);
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(1207, 569, 1460, 596);
                }
                
            }
            //enviar pago
            if(clicEnRectangulo(525, 674,846, 731, x, y))
            {
                bool exitoso;
                if(montoTransferir!=0.0)
                {
                    exitoso=Transaccion::validarTransferencia(&EMISOR, &RECEPCION, montoTransferir, numero,numReceptor );
                    if(exitoso)
                    {
                        int codigoTransaccion = Transaccion::generarCodigoTransaccion();
                        Transaccion::registrarTransaccion(codigoTransaccion, "Transferencia", montoTransferir, EMISOR.getNumeroCuenta(), RECEPCION.getNumeroCuenta());
                        Transaccion::actualizarCuentas(EMISOR.getNumeroCuenta(), RECEPCION.getNumeroCuenta(), montoTransferir);
                        //VUELVE LOS DATOS POR DEFECTO
                        settextstyle(8,0,1);
                        outtextxy(376,644,(char*)"Transaccion Exitosa");
                        delay(1000);
                        menu=TABLERO;
                        return 1;
                    } else 
                    {
                        limpiarChar(monto,19);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(1114, 629, 1454, 690);
                        montoIndex=0;
                        montoTransferir=0;
                    }
                }
            }

            if(clicEnRectangulo(0,0,290,750,x,y)){return 0;}
            }
            delay(100);
        }

    delay(10);  
}
    
    bool manejarClickDepositos() {  
    int numero=0;
    int montoIndex=0, indexCuenta=-1;
    char monto[19];
    char strNumero[100];
    double montoTransferir=0;
    Cuenta RECEPCION;
    
    
    
        settextstyle(8,0,5);
        setcolor(BLACK);
        setbkcolor(WHITE);

        while(true)
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                limpiarBufferTeclado();
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X="<<x<<" Y="<<y;
                
            
                // depostitar corriente
            if (clicEnRectangulo(615, 60, 680, 113, x, y)) {
                
                setfillstyle(SOLID_FILL, WHITE);
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(WHITE);
                numero = cuentas[1].getNumeroCuenta();
                RECEPCION = cuentas[1];
                indexCuenta=1;
                itoa(numero, strNumero, 10);
                outtextxy(400, 550, strNumero);
                delay(50); 
            }

                // depositar Ahorro
            if (clicEnRectangulo(1043, 63,1098, 113, x, y)) {
                numero = cuentas[0].getNumeroCuenta();
                RECEPCION = cuentas[0];
                itoa(numero, strNumero, 10);
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(WHITE);
                outtextxy(400, 550, strNumero);
                delay(50); 
            }

            //monto
            if(clicEnRectangulo(380, 383,741, 444, x, y))
            {
                escribirEnCampo(380, 383,741, 444, monto, 10, montoIndex,0);
                montoTransferir = convertirMontoValido(monto);
                if(montoTransferir==0.0)
                {
                    settextstyle(8,0,1);
                    setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
                    outtextxy(785,415,(char*)"Monto  Invalido");
                    delay(1000);
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(780, 378, 1200, 450);
                }
                
            }
            //enviar pago
            if(clicEnRectangulo(525, 674,846, 731, x, y))
            {
                bool exitoso;
                if(montoTransferir!=0.0)
                {
                    exitoso=Transaccion::depositar(&RECEPCION, montoTransferir);
                    if(exitoso)
                    {
                        limpiarChar(monto,19);
                        montoIndex=0;
                        montoTransferir=0;
                        menu=TABLERO;
                        return 1;
                    } else 
                    {
                        limpiarChar(monto,19);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(390, 383,741, 444);
                        montoIndex=0;
                        montoTransferir=0;
                    }
                }
            }

            if(clicEnRectangulo(0,0,290,750,x,y)){return 0;}
            }
            delay(100);
        }

    delay(10);  
}

 bool manejarClickRetiros() {
    string tarjeta="";
    int montoIndex=0, indexCuenta=-1;
    char monto[19];
    char strTarjeta[100];
    double montoTransferir=0;
    Cuenta ORIGEN;
    
        settextstyle(8,0,5);
        setcolor(BLACK);
        setbkcolor(WHITE);

        while(true)
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                limpiarBufferTeclado();
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X="<<x<<" Y="<<y;
                
            
                // Retirar corriente
            if (clicEnRectangulo(615, 60, 680, 113, x, y)) {
                
                setfillstyle(SOLID_FILL, WHITE);
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(WHITE);
                tarjeta = cuentas[1].getTrajeta();
                ORIGEN = cuentas[1];
                indexCuenta=1;
                strcpy(strTarjeta,tarjeta.c_str());
                outtextxy(400, 406, strTarjeta);
                delay(50); 
            }

                // Retirar Ahorro
            if (clicEnRectangulo(1043, 63,1098, 113, x, y)) {
                tarjeta = cuentas[0].getTrajeta();
                ORIGEN = cuentas[0];
                strcpy(strTarjeta,tarjeta.c_str());
                settextstyle(8,0,5);
                setcolor(BLACK);
                setbkcolor(WHITE);
                outtextxy(400, 406, strTarjeta);
                delay(50); 
            }

            //monto
            if(clicEnRectangulo(402, 530,734, 584, x, y))
            {
                escribirEnCampo(402, 530,734, 584, monto, 10, montoIndex,0);
                montoTransferir = convertirMontoValido(monto);
                if(montoTransferir==0.0)
                {
                    settextstyle(8,0,1);
                    setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
                    outtextxy(785,565,(char*)"Monto  Invalido");
                    delay(1000);
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(775, 517, 1035, 584);
                }
                
            }
            //Retirar
            if(clicEnRectangulo(525, 674,846, 731, x, y))
            {
                bool exitoso;
                if(montoTransferir>0.0)
                {
                    exitoso=Transaccion::retirar(&ORIGEN, montoTransferir);
                    if(exitoso)
                    {
                        limpiarChar(monto,19);
                        montoIndex=0;
                        montoTransferir=0;
                        menu=TABLERO;
                        return 1;
                    } else 
                    {
                        limpiarChar(monto,19);
                        setfillstyle(SOLID_FILL, WHITE);
                        bar(775, 517, 1035, 584);
                        montoIndex=0;
                        montoTransferir=0;
                    }
                }
            }

            if(clicEnRectangulo(0,0,290,750,x,y)){return 0;}
            }
            delay(100);
        }

    delay(10);  
}

bool manejarClickPerfil() {
    int NombreIndex=0, usuarioIndex=0;
    char Nombre[19];
    char Usuario[19];
    Cuenta ORIGEN;
    
        settextstyle(8,0,5);
        setcolor(BLACK);
        setbkcolor(WHITE);

        while(true)
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                limpiarBufferTeclado();
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X="<<x<<" Y="<<y;
                

            //Nombre
            if(clicEnRectangulo(363, 66,948, 125, x, y))
            {
                escribirEnCampo(363, 66,948, 125, Nombre, 10, NombreIndex,0);
                
            }

            //Usuario
            if(clicEnRectangulo(363, 205,948, 272, x, y))
            {
                escribirEnCampo(363, 205,948, 272, Usuario, 10, usuarioIndex,0);
                
            }

            if(clicEnRectangulo(0,0,290,750,x,y)){return 0;}
            }
            delay(100);
        }

    delay(10);  
}

    void dibujarMenu(int codigo, Menu &estado)
    {
        bool volver=false;
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
                    cuentas->mostrarTransacciones(cuentas[0].getNumeroCuenta(),cuentas[1].getNumeroCuenta());   
                    break;
                case TRANSFERENCIAS:  
                    transferenciasUI();
                    mostrarCuentas();
                    volver=manejarClickOperaciones();
                    if(volver)
                    {
                    Cuenta::cargarCuentas(codigo, cuentas);
                    panelUsuario(); 
                    cliente.mostrarCliente();
                    mostrarCuentas();
                    cuentas->mostrarTransacciones(cuentas[0].getNumeroCuenta(),cuentas[1].getNumeroCuenta());
                    }
                    break;
                case DEPOSITOS: 
                depositosUI();
                mostrarCuentas();
                volver=manejarClickDepositos();
                if(volver)
                    {
                    Cuenta::cargarCuentas(codigo, cuentas);
                    panelUsuario(); 
                    cliente.mostrarCliente();
                    mostrarCuentas();
                    cuentas->mostrarTransacciones(cuentas[0].getNumeroCuenta(),cuentas[1].getNumeroCuenta());
                    }
                break;

                case RETIROS:
                retirosUI();
                mostrarCuentas();
                volver=manejarClickRetiros();
                if(volver)
                    {
                    Cuenta::cargarCuentas(codigo, cuentas);
                    panelUsuario(); 
                    cliente.mostrarCliente();
                    mostrarCuentas();
                    cuentas->mostrarTransacciones(cuentas[0].getNumeroCuenta(),cuentas[1].getNumeroCuenta());
                    }
                break;
                    
                case PERFIL:
                    perfilUI();
                    manejarClickPerfil();
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
            cuentas->mostrarTransacciones(cuentas[0].getNumeroCuenta(),cuentas[1].getNumeroCuenta());
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