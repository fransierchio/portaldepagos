#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Transaccion
{
private:
    int codigoTransaccion;
    string descripcion;
    double monto;
    Cuenta* cuentaEmisor;   
    Cuenta* cuentaReceptor; 
    string tarjeta;
    string icono;
public:
    Transaccion(int cod, const string& desc, double monto, Cuenta* emisor, Cuenta* receptor = nullptr, string tarjeta="")
        : codigoTransaccion(cod), descripcion(desc), monto(monto), cuentaEmisor(emisor), cuentaReceptor(receptor), tarjeta(tarjeta) {}
   
     static int generarCodigoTransaccion() {
        srand(time(0));
        return rand() % 1000000 + 100000;
    }

     static void registrarTransaccion(int codigo, const string& descripcion, double monto, int cuentaOrigen, int cuentaReceptor, const string& tarjeta = "") {
        ofstream archivo("transacciones.txt", ios::app);
        archivo << codigo << ";" << descripcion << ";" << monto << ";" 
                << cuentaOrigen << ";" << cuentaReceptor << ";" << tarjeta << endl;
        archivo.close();
    }

    static bool validarTransferencia(Cuenta* cuentaOrigen, Cuenta* cuentaReceptor, double monto, int origen, int receptor) {
        if (!cuentaOrigen || !cuentaReceptor) 
        { 
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            settextstyle(8,0,1);
            outtextxy(376,644,(char*)"Una de las cuentas no está seleccionada.");
            delay(1000);
            setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
            bar(350, 620, 1041, 658);
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            return false;
        }
        if (origen == receptor) {
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            settextstyle(8,0,1);
            outtextxy(376,644,(char*)"La cuenta de origen y receptor no pueden ser la misma.");
            delay(1000);
            setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
            bar(350, 620, 1041, 662);
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            return false;
        }
        if (monto <= 0) {
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            settextstyle(8,0,1);
            outtextxy(376,644,(char*)"Error: El monto debe ser mayor que cero.");
            delay(1000);
            setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
            bar(350, 620, 1041, 658);
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            return false;
        }
        if (cuentaOrigen->getBalance() < monto) {
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            settextstyle(8,0,1);
            outtextxy(376,644,(char*)"Error: Fondos insuficientes");
            delay(1000);
            setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
            bar(350, 620, 1041, 658);
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            return false;
        }
        if(cuentaReceptor->getCodigo()==0)
        { 
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            settextstyle(8,0,1);
            outtextxy(376,644,(char*)"Cuenta invalida");
            delay(1000);
            setfillstyle(SOLID_FILL, COLOR(0xf9, 0xfa, 0xfb));
            bar(350, 620, 1041, 658);
            setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
            return false;}
        return true;
    }

    static void actualizarCuentas(int numeroCuentaOrigen, int numeroCuentaReceptor, double monto) {
    ifstream archivoEntrada("cuentas.txt");
    ofstream archivoTemporal("temp.txt");
    string linea;

    while (getline(archivoEntrada, linea)) {
        int numeroCuenta;
        string tipoCuenta;
        double balance;
        string cedula;
        string tarjeta;

        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);

        numeroCuenta = stoi(linea.substr(0, pos1));
        tipoCuenta = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        balance = stod(linea.substr(pos2 + 1, pos3 - pos2 - 1));
        cedula = linea.substr(pos3 + 1, pos4 - pos3 - 1);
        tarjeta = linea.substr(pos4 + 1);

        if (numeroCuenta == numeroCuentaOrigen) {
            balance -= monto;
        } else if (numeroCuenta == numeroCuentaReceptor) {
            balance += monto;
        }

        // Escribir los datos actualizados al archivo temporal
        archivoTemporal << numeroCuenta << ";" << tipoCuenta << ";" << balance << ";" 
                        << cedula << ";" << tarjeta << endl;
    }

    archivoEntrada.close();
    archivoTemporal.close();

    // Reemplazar el archivo original con el archivo temporal
    remove("cuentas.txt");
    rename("temp.txt", "cuentas.txt");
}

static bool depositar(Cuenta* cuentaReceptor, double monto) {
    if (!cuentaReceptor) {
        setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
        settextstyle(8, 0, 1);
        outtextxy(376, 644, (char*)"Error: La cuenta no está seleccionada.");
        delay(1000);
        return false;
    }

    if (monto <= 0) {
        setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
        settextstyle(8, 0, 1);
        outtextxy(376, 644, (char*)"Error: El monto debe ser mayor que cero.");
        delay(1000);
        return false;
    }

    int numeroCuentaReceptor = cuentaReceptor->getNumeroCuenta();
    actualizarCuentas(0, numeroCuentaReceptor, monto); 

    int codigoTransaccion = generarCodigoTransaccion();
    registrarTransaccion(codigoTransaccion, "Deposito", monto, 0, numeroCuentaReceptor);

    settextstyle(8, 0, 1);
    outtextxy(376, 644, (char*)"Deposito exitoso.");
    delay(1000);

    return true;
}

static bool retirar(Cuenta* cuentaOrigen, double monto) {
    if (!cuentaOrigen) {
        setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
        settextstyle(8, 0, 1);
        outtextxy(376, 644, (char*)"Error: La cuenta no está seleccionada.");
        delay(1000);
        return false;
    }

    if (monto <= 0) {
        setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
        settextstyle(8, 0, 1);
        outtextxy(376, 644, (char*)"Error: El monto debe ser mayor que cero.");
        delay(1000);
        return false;
    }

    if (cuentaOrigen->getBalance() < monto) {
        setbkcolor(COLOR(0xf9, 0xfa, 0xfb));
        settextstyle(8, 0, 1);
        outtextxy(376, 644, (char*)"Error: Fondos insuficientes.");
        delay(1000);
        return false;
    }

    int numeroCuentaOrigen = cuentaOrigen->getNumeroCuenta();
    actualizarCuentas(numeroCuentaOrigen, 0, monto); 

    int codigoTransaccion = generarCodigoTransaccion();
    registrarTransaccion(codigoTransaccion, "Retiro", monto, numeroCuentaOrigen, 0);

    settextstyle(8, 0, 1);
    outtextxy(376, 644, (char*)"Retiro exitoso.");
    delay(1000);

    return true;
}

};

