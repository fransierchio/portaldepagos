#include <iostream>
#include <string>
#include "Cuenta.hpp"
#include <fstream>

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
public:
    Transaccion(int cod, const string& desc, double monto, Cuenta* emisor, Cuenta* receptor = nullptr)
        : codigoTransaccion(cod), descripcion(desc), monto(monto), cuentaEmisor(emisor), cuentaReceptor(receptor) {}
   
   
};

