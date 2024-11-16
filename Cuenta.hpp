#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Cuenta {
private:
    int numeroCuenta;
    string descripcion;
    double saldo;
    int codigoCliente;
    string tarjeta;

public:
    Cuenta(int numeroCuenta, const string& descripcion, double saldo, int codigoCliente,const string& tarjeta)
        : numeroCuenta(numeroCuenta), descripcion(descripcion), saldo(saldo), codigoCliente(codigoCliente), tarjeta(tarjeta) {}

    void mostrarCuenta(int movimientoX)  
    {
        char strCuenta[100];
        char strTipo[100];
        char strSaldo[100];
        char strTarjeta[100];

        strcpy(strTipo,descripcion.c_str());
        itoa(numeroCuenta,strCuenta,10);
        gcvt(saldo,10,strSaldo);
        strcpy(strTarjeta,tarjeta.c_str());

        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 2);

        outtextxy(770-movimientoX, 85, strCuenta);
        outtextxy(770-movimientoX, 60, strTipo);
        if(movimientoX!=0)
        {
            setbkcolor(COLOR(0x32, 0x32, 0x33));
            setcolor(COLOR(0xf7,0xd2,0x74));
            outtextxy(780-movimientoX, 132, (char*)"SALDO($):");
            outtextxy(780-movimientoX, 160, strSaldo);
            settextstyle(8, 0, 1);
            outtextxy(820-movimientoX, 200, strTarjeta);
        } else 
        {
            setbkcolor(COLOR(0x5f, 0x17, 0xea));
            setcolor(COLOR(0xf7,0xd2,0x74));
            outtextxy(780-movimientoX, 132, (char*)"SALDO($):");
            outtextxy(780-movimientoX, 160, strSaldo);
            settextstyle(8, 0, 1);
            outtextxy(817-movimientoX, 200, strTarjeta);
        }
        
    }

    static void cargarCuentas(int codigoCliente) 
    {
        ifstream archivo("cuentas.txt");
        string linea, tarjeta;
        int numCuenta, codigo;
        string descripcion;
        double saldo;
        bool estado;

        int movimientoX=0;

        while (getline(archivo, linea)) 
        {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);
            int pos5 = linea.find(';', pos4 + 1);

            numCuenta = stoi(linea.substr(0, pos1)); 
            descripcion = linea.substr(pos1 + 1, pos2 - pos1 - 1); 
            saldo = stod(linea.substr(pos2 + 1, pos3 - pos2 - 1)); 
            codigo = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1)); 
            tarjeta = linea.substr(pos4 + 1); 

            if (codigo == codigoCliente) 
            {
                Cuenta cuenta(numCuenta, descripcion, saldo, codigo, tarjeta);
                cuenta.mostrarCuenta(movimientoX);
                movimientoX+=417;
            }
        }
}
};
