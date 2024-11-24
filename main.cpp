#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include "Usuario.hpp"
#include "Cliente.hpp"
#include "Cuenta.hpp"
#include "Transaccion.hpp"
#include "validaciones.hpp"

using namespace std;


enum Menu { TABLERO, TRANSFERENCIAS, DEPOSITOS, RETIROS, PERFIL, CERRAR_SESION, PANEL,CREAR,MODIFICAR,SOLICITUDES};

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


void mostrarMensajeError(int x, int y, char* mensaje) {
    setcolor(RED);
    outtextxy(x, y, mensaje);
}

void limpiarMensajeError(int x1, int y1, int x2, int y2) {
    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
    bar(x1, y1, x2, y2);
}
bool obtenerDatosCompletos(int codigo, char* nombre, char* usuario, char* clave, char* numero, char* correo,char *fecha, bool &bloqueo) {

    if (!Usuario::obtenerUsuarioYClave(codigo, usuario, clave, bloqueo)) {
        cerr << "Error: Usuario no encontrado." << endl;
        return false;
    }

    // Extraer datos de Cliente
    cliente = Cliente::cargarCliente(codigo);
    if (cliente.getCodigoCliente() == 0) {
        cerr << "Error: Cliente no encontrado." << endl;
        return false;
    }

    strcpy(nombre, cliente.getNombre().c_str());
    strcpy(numero, cliente.getTelefono().c_str());
    strcpy(correo, cliente.getCorreo().c_str());
    strcpy(fecha, cliente.getFecha().c_str());

    return true;
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
        char pass_text[100];
        int textLen = strlen(texto);
        setbkcolor(WHITE);
        setcolor(BLACK);

        if (!oculto) {
        outtextxy(left + 60, top + 20, texto);
    }   else {
        for (int j = 0; j < textLen; j++) {
            pass_text[j] = pass;
        }
        pass_text[textLen] = '\0';
        outtextxy(left + 60, top + 20, pass_text);
    }

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
                    bar(left + 60, top + 10, right - 10, bottom - 2);
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

//INTERFACES
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
    void directorioUI()
    {
        readimagefile("directorio.jpg",0,0,1500,750);
        Cuenta::mostrarTodasLasCuentas();
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
        readimagefile("panelAdmin.jpg", 0, 0, windowWidth, windowHeight);
    }
    void crearUsuarioUI()
    {
         readimagefile("crearUser.jpg", 0, 0, windowWidth, windowHeight);
    }
    void modificarUsuarioUI()
    {
         readimagefile("modificarUser.jpg", 0, 0, windowWidth, windowHeight);
    }
    void solicitudesUI()
    {
         readimagefile("solicitudes.jpg", 0, 0, windowWidth, windowHeight);
    }
    void ticketUI()
    {
        readimagefile("ticket.jpg", 0, 0, windowWidth, windowHeight);
    }

    

void manejarTicketUI() {
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(8, 0, 2);
    char codigo[20] = "";
    int codigoInt=0;
    int codigoIndex = 0;
    bool existe = false;
    bool notificacionEnviada = false; 
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            cout << "X: " << x << " Y: " << y << endl;
            limpiarBufferTeclado();
        }

        // Campo Codigo
        if (clicEnRectangulo(350, 190, 810, 230, x, y)) {
            escribirEnCampo(350, 190, 810, 230, codigo, 7, codigoIndex, 0);
            codigoInt = filtrarYConvertirChar(codigo);
            existe = Usuario::existeCodigo(codigoInt);
        }


        // Campo Enviar
        if (clicEnRectangulo(890, 165, 1210, 234, x, y)) {
            if (existe) {
                setcolor(GREEN);  
                outtextxy(350, 260, "Codigo valido");
                Usuario::agregarNotificacion(codigoInt);
                notificacionEnviada = true;
                delay(1000);
                LoginInterfaz();
                break;
            }else {
            setcolor(RED);  
            outtextxy(350, 260, "invalido");
            delay(2000);
        }
        }

   
        if (notificacionEnviada) {
            setcolor(GREEN);
            outtextxy(350, 300, "Notificacion enviada correctamente!");
            delay(1000);  
            break; 
        }

        // Regresar
        if (clicEnRectangulo(567, 335, 887, 410, x, y)) {
            LoginInterfaz();
            break;
        }

        delay(10);  
    }
}

bool manejarClickSolicitudes()
{
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(8, 0, 2);
    char codigo[20] = "";
    int codigoInt=0;
    int codigoIndex = 0;
    bool eliminado = false;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            cout << "X: " << x << " Y: " << y << endl;
            limpiarBufferTeclado();
        

        // Campo Codigo
        if (clicEnRectangulo(350, 138, 810, 174, x, y)) {
            escribirEnCampo(350, 138, 810, 174, codigo, 7, codigoIndex, 0);
            codigoInt = filtrarYConvertirChar(codigo);
            eliminado = Usuario::existeCodigo(codigoInt);
        }


        // Campo Enviar
        if (clicEnRectangulo(906, 118, 1210, 184, x, y)) {
            if (eliminado) {
                setcolor(GREEN);  
                outtextxy(390, 213, "Eliminando...");
                Usuario::eliminarNotificacion(codigoInt);
                delay(1000);
                menu==PANEL;
                return true;
            }else {
            setcolor(RED);  
            outtextxy(350, 260, "invalido");
            delay(2000);
        }
        }

        if (clicEnRectangulo(0, 0, 290, 750, x, y)) 
            {
                return 0;
            }
        }


        delay(10);  
    }
}

    int manejarClickLogin() {
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 4);
        while (true) {
            if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X: "<<x<<" Y: "<<y<<endl;
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

            // Ticket
            if (clicEnRectangulo(1130, 685, 1327, 718, x, y)) {
                ticketUI();
                manejarTicketUI();
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

    void manejarMenu(int codigo)
    {
        if(codigo!=30737409)
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
        } else 
        {
            // PANEL
            if (clicEnRectangulo(30, 119, 250, 166, x, y)) {menu= PANEL;}

           // CREAR
            if (clicEnRectangulo(30, 190, 260, 240, x, y)) {menu = CREAR;}

            // MODIFICAR
            if (clicEnRectangulo(30, 256, 265, 304, x, y)) {menu = MODIFICAR;}

            // SOLICITUDES
            if (clicEnRectangulo(30, 325, 250, 374, x, y)) {menu = SOLICITUDES;}
            
            // Opción CERRAR SESION 
            if (clicEnRectangulo(30, 670, 250, 730, x, y)) {menu= CERRAR_SESION;}

            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                cout<<"X="<<x<<" Y="<<y;
            }

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
                settextstyle(8,0,5);
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
                settextstyle(8,0,5);
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
            //Directorio
            if (clicEnRectangulo(315, 539, 378, 587, x, y)) 
            {
                directorioUI();
                delay(4500);
                transferenciasUI();
                mostrarCuentas();
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
    char monto[19]="";
    char strNumero[100]="";
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
                settextstyle(8,0,5);
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
    char monto[19]="";
    char strTarjeta[100]="";
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
                settextstyle(8,0,4);
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
                        bar(400, 517, 743, 584);
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

bool manejarClickPerfil(int codigo) 
{
    char Nombre[100];
    char User[19];
    char Clave[19];
    char Numero[100];
    char correo[100];
    char fecha[100];
    bool bloqueo;
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(8, 0, 2);


    obtenerDatosCompletos(codigo, Nombre,User,Clave,Numero,correo,fecha,bloqueo);
    int NombreIndex = strlen(Nombre);
    int usuarioIndex = strlen(User);
    int claveIndex = strlen(Clave);
    int numeroIndex = strlen(Numero);
    int correoIndex = strlen(correo);

    bool validaciones[5];
    for(int i=0;i<5;i++)
    {
        validaciones[i]=1;
    }
    //por defecto
    settextstyle(8,0,2);
    setcolor(BLACK);
    setbkcolor(WHITE);

        while(true)
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                limpiarBufferTeclado();
                cout<<"X="<<x<<" Y="<<y;
                

            //Nombre
            if(clicEnRectangulo(363, 66,948, 125, x, y))
            {
                escribirEnCampo(300, 66,948, 125, Nombre, 25, NombreIndex,0);
                validaciones[0]=validarNombre(Nombre);
                if (!validaciones[0]) {
                mostrarMensajeError(991, 102, "invalido");
            } else {
                limpiarMensajeError(987, 60, 1297, 118);
            }
            }

            //Usuario
            if(clicEnRectangulo(363, 205,948, 272, x, y))
            {
                escribirEnCampo(300, 205,948, 272, User, 10, usuarioIndex,0);
                validaciones[1]=validarUsuario(User,codigo);
                if (!validaciones[1]) {
                mostrarMensajeError(991, 241, "invalido");
            } else {
                limpiarMensajeError(980, 204, 1300, 270);
            }
            }
            
            //clave
            if(clicEnRectangulo(363, 371,948, 425, x, y))
            {
                escribirEnCampo(300, 371,948, 425, Clave, 10, claveIndex,0);
                validaciones[2]=validarClave(Clave);
                if (!validaciones[2]) {
                mostrarMensajeError(991, 390, "invalido");
            } else {
                limpiarMensajeError(981, 366, 1320, 424);
            }
            }

            //numero
            if(clicEnRectangulo(363, 517,948, 567, x, y))
            {
                escribirEnCampo(300, 517,948, 567, Numero, 16, numeroIndex,0);
                validaciones[3]=validarNumero(Numero);
                if (!validaciones[3]) {
                mostrarMensajeError(991, 550, "invalido");
            } else {
                limpiarMensajeError(980, 517, 1300, 575);
            }
            }

            //correo
            if(clicEnRectangulo(363, 667,948, 717, x, y))
            {
                escribirEnCampo(300, 667,948, 717, correo, 30, correoIndex,0);
                validaciones[4]=validarCorreo(correo,codigo);
                if (!validaciones[4]) {
                mostrarMensajeError(991, 692, "invalido");
            } 
                else 
                {
                limpiarMensajeError(983, 654, 1154, 726);
                }
            }

            //validar
            if(clicEnRectangulo(1179, 665,1487, 731, x, y))
            {
                bool valido=true;
                for(int i=0;i<5;i++)
                {
                    if(!validaciones[i])
                    {
                        valido=false;
                    }
                }

                if(valido)
                {
                    Usuario::actualizarUsuario(codigo,User,Clave,bloqueo);
                    Cliente::actualizarCliente(codigo,Nombre,correo,Numero,"");
                    menu=TABLERO;
                    return true;
                } else 
                {
                    cout<<"Campos invalidos";
                }
            }


            if(clicEnRectangulo(0,0,290,750,x,y)){return 0;}
            }
            delay(10);
        }
    delay(10);  
}  

bool manejarClickCrearUser(int codigo) 
{
    char Nombre[100]="";
    char User[19]="";
    char Clave[19]="";
    char Numero[100]="";
    char correo[100]="";
    char fecha[100]="";
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(8, 0, 2);

    int NombreIndex = 0;int usuarioIndex = 0;int claveIndex = 0;
    int numeroIndex = 0;int correoIndex = 0;int fechaIndex = 0;

    bool validaciones[6];
    for(int i=0;i<5;i++)
    {
        validaciones[i]=0;
    }
    //por defecto
    settextstyle(8,0,2);
    setcolor(BLACK);
    setbkcolor(WHITE);

        while(true)
        {
            
            if (ismouseclick(WM_LBUTTONDOWN)) 
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                limpiarBufferTeclado();
                cout<<"X="<<x<<" Y="<<y;
                

            //Nombre
            if(clicEnRectangulo(363, 66,948, 125, x, y))
            {
                escribirEnCampo(300, 66,948, 125, Nombre, 25, NombreIndex,0);
                validaciones[0]=validarNombre(Nombre);
                if(validaciones[0]!=1){outtextxy(511,27,(char*)"invalido");} else 
                {
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(494,25,633,47);
                }
            }

            //Usuario
            if(clicEnRectangulo(363, 205,948, 272, x, y))
            {
                escribirEnCampo(300, 205,948, 272, User, 10, usuarioIndex,0);
                validaciones[1]=validarUsuario(User,codigo);
                if(validaciones[1]!=1){outtextxy(511,173,(char*)"invalido");} else 
                {
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(494,167,674,195);
                }
            }
            
            //clave
            if(clicEnRectangulo(363, 371,948, 425, x, y))
            {
                escribirEnCampo(300, 371,948, 425, Clave, 10, claveIndex,0);
                validaciones[2]=validarClave(Clave);
                if(validaciones[2]!=1){outtextxy(511,327,(char*)"invalido");} else 
                {
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(494,312,633,349);
                }
            }

            //numero
            if(clicEnRectangulo(363, 517,948, 567, x, y))
            {
                escribirEnCampo(300, 517,948, 567, Numero, 16, numeroIndex,0);
                validaciones[3]=validarNumero(Numero);
                if(validaciones[3]!=1){outtextxy(511,478,(char*)"invalido");} else 
                {
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(494,465,633,494);
                }
            }

            //correo
            if(clicEnRectangulo(363, 667,948, 717, x, y))
            {
                escribirEnCampo(300, 667,948, 717, correo, 30, correoIndex,0);
                validaciones[4]=validarCorreo(correo,codigo);
                if(validaciones[4]!=1){outtextxy(646,695,(char*)"invalido");} else 
                {
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(640,616,887,640);
                }
            }

            //fecha
             if(clicEnRectangulo(1013, 66,1451, 125, x, y))
            {
                escribirEnCampo(1013, 66,1451, 125, fecha, 30, fechaIndex,0);
                validaciones[5]=validarFechaNacimiento(fecha);
                if(validaciones[5]!=1){outtextxy(1050,164,(char*)"invalido");} else 
                {
                    setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
                    bar(1016,155,1393,188);
                }
            }

            //validar
            if(clicEnRectangulo(1179, 665,1487, 731, x, y))
            {
                bool valido=true;
                for(int i=0;i<6;i++)
                {
                    if(!validaciones[i])
                    {
                        valido=false;
                    }
                }

                if(valido)
                {
                    int codigoCte=0;
                    codigoCte=Usuario::crearUsuario(User, Clave);
                    Cliente::crearCliente(Nombre,correo,Numero,fecha,codigoCte);
                    Cuenta::crearCuentas(codigoCte);
                    menu=PANEL;
                    return true;
                } else 
                {
                    cout<<"Campos invalidos";
                }
            }


            if(clicEnRectangulo(0,0,290,750,x,y)){return 0;}
            }
            delay(10);
        }
    delay(10);  
} 

bool manejarClickModificar(int codigo) 
{
    char Nombre[100]="";
    char User[19]="";
    char Clave[19]="";
    char Numero[100]="";
    char correo[100]="";
    char fecha[100]="";
    bool bloqueo;
    bool codigoValido = false;
    char codigoIngresado[10]="";  
    int codigoIndex = 0;
    char bloqueoChar[2];
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(8, 0, 2);

    int NombreIndex = 0, usuarioIndex = 0, claveIndex = 0;
    int numeroIndex = 0, correoIndex = 0, fechaIndex = 0, bloqueoIndex=1;
    bool validaciones[7] = {true, true, true, true, true, true, true};

    while (!codigoValido) 
    {
        if (ismouseclick(WM_LBUTTONDOWN)) 
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            limpiarBufferTeclado();

            // Campo para ingresar el código
            if (clicEnRectangulo(565, 81, 1135, 132, x, y)) 
            {
                escribirEnCampo(565, 81, 1135, 132, codigoIngresado, 10, codigoIndex, 0);
            }

            if (codigoIngresado[0] != '\0') 
            {
                int codigoTemp = atoi(codigoIngresado); 
                if (Usuario::existeCodigo(codigoTemp)) 
                {
                    codigo = codigoTemp;
                    codigoValido = obtenerDatosCompletos(codigo, Nombre, User, Clave, Numero, correo, fecha, bloqueo);

                    if (codigoValido) 
                    {
                        NombreIndex = strlen(Nombre);
                        usuarioIndex = strlen(User);
                        claveIndex = strlen(Clave);
                        numeroIndex = strlen(Numero);
                        correoIndex = strlen(correo);
                        fechaIndex = strlen(fecha);

                        bloqueoChar[0] = (bloqueo ? '1' : '0');
                        bloqueoChar[1] = '\0';
                        cout << "Codigo válido, datos cargados." << endl;
                    } 
                } 
                else 
                {
                    outtextxy(600, 150, "Codigo invalido.");
                }
            }

            if (clicEnRectangulo(0, 0, 290, 750, x, y)) 
            {
                return false;
            }
        }

        delay(10);
    }

    while(true)
    {
        if (ismouseclick(WM_LBUTTONDOWN)) 
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            limpiarBufferTeclado();
            cout << "X=" << x << " Y=" << y;

            // Nombre
            if(clicEnRectangulo(363, 235,948, 285, x, y))
            {
                escribirEnCampo(363, 235,948, 285, Nombre, 25, NombreIndex, 0);
                validaciones[0] = validarNombre(Nombre);
                if (!validaciones[0]) {
                mostrarMensajeError(498, 185, "Nombre invalido");
            } else {
                limpiarMensajeError(495, 178, 726, 205);
            }
                
            }

            // Usuario
            if(clicEnRectangulo(359, 372,943, 426, x, y))
            {
                escribirEnCampo(359, 372,943, 426, User, 10, usuarioIndex, 0);
                validaciones[1] = validarUsuario(User, codigo);
                if (!validaciones[1]) {
                mostrarMensajeError(498, 330, "Usuario invalido");
            } else {
                limpiarMensajeError(490, 327, 712, 350);
            }
            }
            
            // Clave
            if(clicEnRectangulo(1013, 371,1452, 425, x, y))
            {
                escribirEnCampo(1013, 371,1452, 425, Clave, 10, claveIndex, 0);
                validaciones[2] = validarClave(Clave);
                 if (!validaciones[2]) {
                mostrarMensajeError(1120, 330, "Clave invalida");
            } else {
                limpiarMensajeError(1115, 325, 1300, 347);
            }
            }

            // Número
            if(clicEnRectangulo(360, 514,948, 575, x, y))
            {
                escribirEnCampo(360, 514,948, 575, Numero, 16, numeroIndex, 0);
                validaciones[3] = validarNumero(Numero);
                if (!validaciones[3]) {
                mostrarMensajeError(503, 475, "Numero invalido");
            } else {
                limpiarMensajeError(484, 470, 726, 496);
            }
            }

            // Correo
            if(clicEnRectangulo(357, 667,948, 723, x, y))
            {
                escribirEnCampo(357, 667,948, 723, correo, 30, correoIndex, 0);
                validaciones[4] = validarCorreo(correo, codigo);
                if (!validaciones[4]) {
                mostrarMensajeError(647, 623, "Correo invalido");
            } else {
                limpiarMensajeError(640, 610, 890, 640);
            }
            }

            // Fecha
            if(clicEnRectangulo(1012, 226,1434, 286, x, y))
            {
                escribirEnCampo(1012, 226,1434, 286, fecha, 30, fechaIndex, 0);
                validaciones[5]= validarFechaNacimiento(fecha);
                if (!validaciones[5]) {
                mostrarMensajeError(1205, 153, "Fecha invalida");
            } else {
                limpiarMensajeError(1195, 140, 1450, 170);
            }
            }

            // Bloqueo
            if(clicEnRectangulo(1011, 511,1443, 579, x, y)) 
            {
                escribirEnCampo(1011, 511,1443, 579, bloqueoChar, 2, bloqueoIndex, 0);
                validaciones[6]= validacionBloqueo(bloqueoChar);
                bloqueo = (bloqueoChar[0] == '1'); 
                if (!validaciones[6]) {
                mostrarMensajeError(1045, 615, "Bloqueo invalido");
            } else {
                limpiarMensajeError(1040, 600, 1250, 645);
            }
            }

            // Validar
            if(clicEnRectangulo(1179, 665,1487, 731, x, y))
            {
                bool valido = true;
                for(int i = 0; i < 8; i++)
                {
                    if(!validaciones[i])
                    {
                        valido = false;
                        break;
                    }
                }

                if(valido)
                {
                    
                    Usuario::actualizarUsuario(codigo, User, Clave, bloqueo);
                    Cliente::actualizarCliente(codigo, Nombre, correo, Numero, fecha);
                    menu = TABLERO;
                    return true;
                } 
                else 
                {
                    cout << "Campos inválidos";
                }
            }

            if(clicEnRectangulo(0,0,290,750,x,y)){ return 0; }
        }
        delay(10);
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
                    volver=manejarClickPerfil(codigo);
                    if(volver)
                    {
                    cliente = Cliente::cargarCliente(codigo);
                    Cuenta::cargarCuentas(codigo, cuentas);
                    panelUsuario(); 
                    cliente.mostrarCliente();
                    mostrarCuentas();
                    cuentas->mostrarTransacciones(cuentas[0].getNumeroCuenta(),cuentas[1].getNumeroCuenta());
                    }
                    break;
                case PANEL:
                    panelAdmin();
                    Usuario::mostrarTodosLosCodigos();
                    break; 
                case CREAR:
                    crearUsuarioUI();
                    volver=manejarClickCrearUser(codigo);
                    if(volver)
                    {
                        panelAdmin();
                        Usuario::mostrarTodosLosCodigos();
                    }

                    break; 
                case MODIFICAR:
                    modificarUsuarioUI();
                    volver=manejarClickModificar(codigo);
                    if(volver)
                    {
                        panelAdmin();
                        Usuario::mostrarTodosLosCodigos();
                    }
                    break; 
                case SOLICITUDES:
                    solicitudesUI();
                    Usuario::mostrarNotificaciones();
                    volver=manejarClickSolicitudes();
                    if(volver)
                    {
                        panelAdmin();
                        Usuario::mostrarTodosLosCodigos();
                    }
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

    while(true)
    {
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
        } else 
        {
            menu=PANEL;
            panelAdmin();
            Usuario::mostrarTodosLosCodigos();
        }

        while(menu!=CERRAR_SESION)
        {
            Menu estado = menu;
            manejarMenu(codigo);
            dibujarMenu(codigo, estado);
            delay(5);
        }
        
        limpiarChar(usuario,19);
        limpiarChar(contrasena,19);
        userIndex=0;
        passIndex=0;

    }
        closegraph();
    }

};

int main() {

    Sistema ugmaPay(1500, 750);  
    ugmaPay.iniciarSistema();   
    return 0;
}