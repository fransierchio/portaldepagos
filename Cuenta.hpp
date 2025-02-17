#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Cuenta 
{
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
    
    void setDefault()
    {
        numeroCuenta=0, descripcion="", saldo=0.0, codigoCliente=0, tarjeta="";
    }

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

    int getNumeroCuenta() { return numeroCuenta; }
    double getBalance() { return saldo; }
    int getCodigo(){return codigoCliente;}
    string getTrajeta(){return tarjeta;}

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
         return;
    }

    static Cuenta cargarCuenta(int codigoCliente, int numReceptor) 
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
            
            if(codigoCliente==codigo && numReceptor==numCuenta)
            {
                return Cuenta(numCuenta, descripcion, saldo, codigo, tarjeta);
            }
            
        }
         archivo.close();
    }

    static int buscarCodigo(int receptor) 
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

            if (receptor == numCuenta) 
            {
                return codigo;
            }
        }
        archivo.close();
        return 0;
    }


void mostrarTransacciones(int cuenta1, int cuenta2) {
    ifstream archivo("transacciones.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de transacciones." << endl;
        return;
    }

    int totalTransacciones = 0;

    // Primera pasada: contar la cantidad de transaciones
    string linea;
    while (getline(archivo, linea)) {
        int pos3 = linea.find(';', linea.find(';', linea.find(';') + 1) + 1);
        int pos4 = linea.find(';', pos3 + 1);

        int cuentaOrigen = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
        int cuentaDestino = stoi(linea.substr(pos4 + 1));

        if (cuentaOrigen == cuenta1 || cuentaOrigen == cuenta2 || 
            cuentaDestino == cuenta1 || cuentaDestino == cuenta2) {
            totalTransacciones++;
        }
    }

    archivo.clear();            
    archivo.seekg(0, ios::beg);     // Volver al inicio del archivo

    int inicio = max(0, totalTransacciones - 7);
    int actual = 0;

    int x = 373;   
    int y = 439;    
    int offsetY = 40;
    int yimg=0;


    // Segunda pasada: mostrar solo las ultims 7 transacciones
    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);
        int pos5 = linea.find(';', pos4 + 1);

        int codigoTransaccion = stoi(linea.substr(0, pos1));
        string descripcion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        double monto = stod(linea.substr(pos2 + 1, pos3 - pos2 - 1));
        int cuentaOrigen = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
        int cuentaDestino = stoi(linea.substr(pos4 + 1, pos5 - pos4 - 1));

        string tarjeta = (pos5 != string::npos) ? linea.substr(pos5 + 1) : "";

        if (cuentaOrigen == cuenta1 || cuentaOrigen == cuenta2 || 
            cuentaDestino == cuenta1 || cuentaDestino == cuenta2) {
            if (actual >= inicio) {
                char strID[50], strMonto[50], strCuentas[100], strTarjeta[100];
                itoa(codigoTransaccion, strID, 10);
                gcvt(monto, 10, strMonto);
                int lenMonto = strlen(strMonto);
                if (lenMonto > 0 && strMonto[lenMonto - 1] == '.') {
                    strMonto[lenMonto - 1] = '\0'; 
                }

                if(cuentaOrigen==0)
                {
                    sprintf(strCuentas, " %s        %d ", "EFECTIVO", cuentaDestino);
                } else if (cuentaDestino==0)
                {
                    sprintf(strCuentas, " %d          %s ", cuentaOrigen, "EFECTIVO");
                } else {sprintf(strCuentas, " %d          %d ", cuentaOrigen, cuentaDestino);}
                
                
                if (!tarjeta.empty()) {
                    strcpy(strTarjeta, tarjeta.c_str());
                } else {
                    strcpy(strTarjeta, ""); // Si no hay tarjeta, vacio
                }

                // Dibujar transaccion con coordenadas
                setbkcolor(WHITE);
                setcolor(BLACK);
                settextstyle(8, 0, 1);

                // Mostrar ID
                outtextxy(x + 87, y, strID);

                // Mostrar descripcion
                if(descripcion=="Transferencia")
                {
                    readimagefile("Tranferencias.jpg", 360, 430+yimg, 420, 470+yimg);
                }
                if(descripcion=="Deposito")
                {
                    readimagefile("Depositos.jpg", 360, 430+yimg, 420, 470+yimg);
                }
                if(descripcion=="Retiro")
                {
                    readimagefile("Retiros.jpg", 360, 430+yimg, 420, 470+yimg);
                }


                // Mostrar monto
                outtextxy(x + 591, y, strMonto);

                // Mostrar cuentas
                setcolor(BLACK);
                outtextxy(x+260, y, strCuentas);

                // Mostrar tarjeta si existe
                if (strlen(strTarjeta) > 0) {
                    settextstyle(8, 0, 1);
                    outtextxy(x, y, strTarjeta);
                }

                // Incrementar Y para la siguiente transaccion
                y += offsetY;
                yimg += offsetY;
            }
            actual++;
        }
    }

    archivo.close();
}

    static bool existeNumeroCuenta(int numeroCuenta) {
        ifstream archivo("cuentas.txt");
        if (!archivo.is_open()) return false;

        string linea;
        while (getline(archivo, linea)) {
            int numCuenta = stoi(linea.substr(0, linea.find(';')));
            if (numCuenta == numeroCuenta) {
                archivo.close();
                return true;
            }
        }
        archivo.close();
        return false;
    }

    static bool existeTarjeta(const string &tarjeta) {
        ifstream archivo("cuentas.txt");
        if (!archivo.is_open()) return false;

        string linea;
        while (getline(archivo, linea)) {
            size_t pos = linea.rfind(';');
            string tarjetaGuardada = linea.substr(pos + 1);
            if (tarjetaGuardada == tarjeta) {
                archivo.close();
                return true;
            }
        }
        archivo.close();
        return false;
    }

    static void mostrarTodasLasCuentas() {
        const int maxCuentas = 100;
        Cuenta cuentas[maxCuentas];

        ifstream archivo("cuentas.txt");
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de cuentas." << endl;
            return;
        }

        string linea, tarjeta;
        int numCuenta, codigo;
        string descripcion;
        double saldo;
        int index = 0;

        while (getline(archivo, linea) && index < maxCuentas) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);

            numCuenta = stoi(linea.substr(0, pos1)); 
            descripcion = linea.substr(pos1 + 1, pos2 - pos1 - 1); 
            saldo = stod(linea.substr(pos2 + 1, pos3 - pos2 - 1)); 
            codigo = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1)); 
            tarjeta = linea.substr(pos4 + 1); 

            cuentas[index] = Cuenta(numCuenta, descripcion, saldo, codigo, tarjeta);
            index++;
        }
        archivo.close();

        int startX = 300;
        int startY = 100;
        int offsetX = 100;
        int offsetY = 50;
        int limiteColumnas = 12;

        int x = startX;
        int y = startY;
        int cuentaMostrada = 0;

        for (int i = 0; i < index; ++i) {
            char strCuenta[50];
            itoa(cuentas[i].getNumeroCuenta(), strCuenta, 10);

            setbkcolor(WHITE);
            setcolor(BLACK);
            settextstyle(8, 0, 2);
            outtextxy(x, y, strCuenta);

            cuentaMostrada++;
            if (cuentaMostrada % limiteColumnas == 0) {
                x = startX;
                y += offsetY;
            } else {
                x += offsetX;
            }
        }
}

    static string generarTarjeta() {
        string tarjeta;
        do {
            tarjeta = "4850 4600 ";
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 4; ++j) {
                    tarjeta += to_string(rand() % 10);
                }
                if (i == 0) tarjeta += " ";
            }
        } while (existeTarjeta(tarjeta));
        return tarjeta;
    }

    static int generarNumeroCuenta() {
        int numeroCuenta;
        do {
            numeroCuenta = 100000 + rand() % 900000;  // Generar numero de 6 digitos
        } while (existeNumeroCuenta(numeroCuenta));
        return numeroCuenta;
    }

    static void crearCuentas(int codigoCliente) {
        ofstream archivo("cuentas.txt", ios::app);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo cuentas.txt" << endl;
            return;
        }

        // Crear cuenta corriente
        int numeroCuentaCorriente = generarNumeroCuenta();
        string tarjetaCorriente = generarTarjeta();
        archivo << numeroCuentaCorriente << ";Cuenta corriente;0.00;" << codigoCliente << ";" << tarjetaCorriente << "\n";

        // Crear cuenta de ahorro
        int numeroCuentaAhorro = generarNumeroCuenta();
        string tarjetaAhorro = generarTarjeta();
        archivo << numeroCuentaAhorro << ";Cuenta de ahorros;0.00;" << codigoCliente << ";" << tarjetaAhorro << "\n";

        archivo.close();
    }



};
