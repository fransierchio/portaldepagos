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
    Cuenta() : numeroCuenta(0), descripcion(""), saldo(0.0), codigoCliente(0), tarjeta("") {}
        

    void mostrarCuenta(int tipo)  
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

        if(tipo!=0)
        {
            outtextxy(363, 85, strCuenta);
            outtextxy(363, 60, strTipo);
            setbkcolor(COLOR(0x32, 0x32, 0x33));
            setcolor(COLOR(0xf7,0xd2,0x74));
            outtextxy(363, 132, (char*)"SALDO($):");
            outtextxy(363, 160, strSaldo);
            settextstyle(8, 0, 1);
            outtextxy(403, 200, strTarjeta);
        } else 
        {
            outtextxy(770, 85, strCuenta);
            outtextxy(770, 60, strTipo);
            setbkcolor(COLOR(0x5f, 0x17, 0xea));
            setcolor(COLOR(0xf7,0xd2,0x74));
            outtextxy(780, 132, (char*)"SALDO($):");
            outtextxy(780, 160, strSaldo);
            settextstyle(8, 0, 1);
            outtextxy(817, 200, strTarjeta);
        }
        
    }

    int seleccionarCuenta()
    {
        return numeroCuenta;
    }

    static void cargarCuentas(int codigoCliente, Cuenta *cuentas) 
    {
        ifstream archivo("cuentas.txt");
        string linea, tarjeta;
        int numCuenta, codigo;
        string descripcion;
        double saldo;
        bool estado;

        int index = 0;

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

            if (codigo == codigoCliente && index < 2) 
            {
                cuentas[index]=Cuenta(numCuenta, descripcion, saldo, codigo, tarjeta);
                index++;

            }
        }
         archivo.close();
    }



};
