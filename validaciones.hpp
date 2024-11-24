#include <iostream>
#include <string.h>
#include <ctime>

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

bool validarNombre(char* nombre) {
    if (strlen(nombre) == 0) {
        cout << "El nombre no puede estar vacío." << endl;
        return false;
    }
    for (int i = 0; nombre[i] != '\0'; i++) {
        if (!isalpha(nombre[i]) && nombre[i] != ' ') {
            cout << "El nombre solo puede contener letras y espacios." << endl;
            return false;
        }
    }
    if (strlen(nombre) < 2) {
        cout << "El nombre debe tener al menos 2 caracteres." << endl;
        return false;
    }
    return true;
}

bool validarNumero(char* numero) {
    if (strlen(numero) == 0) {
        cout << "El número no puede estar vacío." << endl;
        return false;
    }
    for (int i = 0; numero[i] != '\0'; i++) {
        if (!isdigit(numero[i])) {
            cout << "El número solo puede contener dígitos." << endl;
            return false;
        }
    }
    if (strlen(numero) < 10 || strlen(numero) > 15) {
        cout << "El número debe tener entre 10 y 15 dígitos." << endl;
        return false;
    }
    return true;
}

bool validarCorreo(char* correo, int codigo) {
    if (strlen(correo) == 0) {
        cout << "El correo no puede estar vacío." << endl;
        return false;
    }
    bool tieneArroba = false, tienePunto = false;
    for (int i = 0; correo[i] != '\0'; i++) {
        if (correo[i] == '@') {
            tieneArroba = true;
        } else if (correo[i] == '.'&&tieneArroba) {
            tienePunto = true;
        }
    }
    if (!tieneArroba || !tienePunto) {
        cout << "El correo debe tener un formato válido (ejemplo@dominio.com)." << endl;
        return false;
    }
    if (!Cliente::VerificarCorreo(correo,codigo)) {
        cout<<"Correo registrado"<<endl;
        return false;
    }
    return true;
}

bool validarClave(char* clave) {
    if (strlen(clave) == 0) {
        cout << "La clave no puede estar vacía." << endl;
        return false;
    }
    if (strlen(clave) < 6) {
        cout << "La clave debe tener al menos 6 caracteres." << endl;
        return false;
    }
    return true;
}

bool validarUsuario(char* usuario, int codigo) {
    if (strlen(usuario) == 0) {
        cout << "El nombre de usuario no puede estar vacio." << endl;
        return false;
    }
    for (int i = 0; usuario[i] != '\0'; i++) {
        if (!isalnum(usuario[i])) {
            cout << "El nombre de usuario solo puede contener letras y numeros" << endl;
            return false;
        }
    }
    if (!Usuario::VerificarUsuario(codigo,usuario)) {
        cout << "El nombre de usuario ya existe." << endl;
        return false;
    }
    return true;
}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool validarFechaNacimiento(const string& fecha) {
    if (fecha.length() != 10) {
        cout << "Formato incorrecto. Debe ser AAAA/MM/DD." << endl;
        return false;
    }

    if (!isdigit(fecha[0]) || !isdigit(fecha[1]) || !isdigit(fecha[2]) || !isdigit(fecha[3]) || fecha[4] != '/' ||
        !isdigit(fecha[5]) || !isdigit(fecha[6]) || fecha[7] != '/' ||
        !isdigit(fecha[8]) || !isdigit(fecha[9])) {
        cout << "Formato incorrecto. Debe ser AAAA/MM/DD." << endl;
        return false;
    }

    // Extraer año, mes y día
    int anio = stoi(fecha.substr(0, 4));
    int mes = stoi(fecha.substr(5, 2));
    int dia = stoi(fecha.substr(8, 2));

    // Validar rango de mes y día
    if (mes < 1 || mes > 12) {
        cout << "Mes inválido." << endl;
        return false;
    }

    if (dia < 1) {
        cout << "Día inválido." << endl;
        return false;
    }

    // Validar el día según el mes
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (esBisiesto(anio)) {
        diasPorMes[1] = 29; // Febrero en año bisiesto
    }

    if (dia > diasPorMes[mes - 1]) {
        cout << "Día inválido para el mes especificado." << endl;
        return false;
    }

    // Validar que la fecha no esté en el futuro
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int anioActual = now->tm_year + 1900;
    int mesActual = now->tm_mon + 1;
    int diaActual = now->tm_mday;

    if (anio > anioActual || 
        (anio == anioActual && mes > mesActual) || 
        (anio == anioActual && mes == mesActual && dia > diaActual)) {
        cout << "La fecha no puede estar en el futuro." << endl;
        return false;
    }

    // Si pasa todas las validaciones
    return true;
}

bool validacionBloqueo(const char* bloqueo) {
    if (strlen(bloqueo) != 1) {
        cout << "Error: Solo se permite un caracter (0 o 1)." << endl;
        return false;
    }

    if (bloqueo[0] == '0' || bloqueo[0] == '1') {
        return true;
    } else {
        cout << "Error: Solo se permiten valores 0 o 1." << endl;
        return false;
    }
}