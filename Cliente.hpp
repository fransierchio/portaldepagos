#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Cliente {
private:
    int codigoCliente;
    string nombre;
    string correo;
    string telefono;
    string fechaNacimiento;
    string icono;


public:
    // Constructor
    Cliente(int codigoCliente,  const string &nombre, const string &birth,  const string &correo,  const string &telefono, const string &icono)
        : codigoCliente(codigoCliente), nombre(nombre),fechaNacimiento(birth), correo(correo), telefono(telefono), icono(icono) {}
    Cliente()
        : codigoCliente(0), nombre(""),fechaNacimiento(""), correo(""), telefono(""), icono("") {}

    string  getNombre(){return nombre;}
    string  getCorreo(){return correo;}
    string  getTelefono(){return telefono;}
    string getFecha(){return fechaNacimiento;}

    void setDefault()
        {
            codigoCliente=0, nombre="",fechaNacimiento="", correo="", telefono="", icono="";
        }

    void mostrarCliente()  
    {
        setbkcolor(COLOR(0x33, 0x33, 0x33));  
        setcolor(WHITE);
        settextstyle(8, 0, 3);

        char strCodigo[100];
        char strNombre[100];
        char strCorreo[100];
        char strTelefono[100];
        char strIcono[100];
        char strNacimiento[100];
        itoa(codigoCliente, strCodigo, 10);  
        strcpy(strNombre, nombre.c_str());  
        strcpy(strCorreo, correo.c_str());  
        strcpy(strTelefono, telefono.c_str());  
        strcpy(strNacimiento, fechaNacimiento.c_str());  
        strcpy(strIcono, icono.c_str()); 

        readimagefile(strIcono, 1214, 66, 1390, 217);
        outtextxy(1170, 380, strCodigo);
        settextstyle(8, 0, 1);
        outtextxy(1170, 290, strNombre);
        settextstyle(8, 0, 3);
        outtextxy(1170, 660, strTelefono);
        settextstyle(8, 0, 2);
        outtextxy(1170, 480, strNacimiento);

        settextstyle(8, 0, 2);  
        //dividir el correo porque puede ser muy grande
        int xCorreo = 1170, yCorreo = 568; 
        for (int i = 0; i < strlen(strCorreo); i += 17) 
        {
            settextstyle(8, 0, 2);
            char subCorreo[18]; 
            strncpy(subCorreo, &strCorreo[i], 17);
            subCorreo[17] = '\0';
            outtextxy(xCorreo, yCorreo, subCorreo);
            yCorreo += 20; 
        }
    }

    void mostrarReceptor()  
    {
        setbkcolor(COLOR(0x33, 0x33, 0x33));  
        setcolor(WHITE);
        settextstyle(8, 0, 3);

        char strNombre[100];
        char strCorreo[100];
        char strTelefono[100];
        char strIcono[100];
        strcpy(strNombre, nombre.c_str());  
        strcpy(strCorreo, correo.c_str());  
        strcpy(strTelefono, telefono.c_str());  
        strcpy(strIcono, icono.c_str()); 

        readimagefile(strIcono, 1214, 66, 1390, 217);
        settextstyle(8, 0, 1);
        outtextxy(1170, 290, strNombre);
        settextstyle(8, 0, 2);
        outtextxy(1170, 480, strTelefono);

        int xCorreo = 1170, yCorreo = 380; 
        for (int i = 0; i < strlen(strCorreo); i += 17) 
        {
            settextstyle(8, 0, 2);
            char subCorreo[18]; 
            strncpy(subCorreo, &strCorreo[i], 17);
            subCorreo[17] = '\0';
            outtextxy(xCorreo, yCorreo, subCorreo);
            yCorreo += 20; 
        }
    }

    static Cliente cargarCliente(int codigoCliente) {
        ifstream archivo("clientes.txt");
        string linea;
        int codigo;
        string nombre, fechaNacimiento, correo, telefono, icon;

        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);
            int pos5 = linea.find(';', pos4 + 1);

            codigo = stoi(linea.substr(0, pos1));  // Código del cliente
            nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);  // Nombre
            fechaNacimiento = linea.substr(pos2 + 1, pos3 - pos2 - 1);  // Fecha de nacimiento
            correo = linea.substr(pos3 + 1, pos4 - pos3 - 1);  // Correo electrónico
            telefono = linea.substr(pos4 + 1, pos5 - pos4 - 1);  // Teléfono
            icon = linea.substr(pos5 + 1); //icono

            if (codigo == codigoCliente) {
                return Cliente(codigo, nombre, fechaNacimiento, correo, telefono,icon);
            }
        }

        return Cliente(0, " ", " ", " ", " "," ");  // Retorna un cliente vacío si no se encuentra el cliente
    }

    static bool VerificarCorreo(string correo_escrito, int codigoCliente) {
        ifstream archivo("clientes.txt");
        string linea;
        int codigo;
        string nombre, fechaNacimiento, correo, telefono, icon;

        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            int pos4 = linea.find(';', pos3 + 1);
            int pos5 = linea.find(';', pos4 + 1);

            codigo = stoi(linea.substr(0, pos1));  // Código del cliente
            nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);  // Nombre
            fechaNacimiento = linea.substr(pos2 + 1, pos3 - pos2 - 1);  // Fecha de nacimiento
            correo = linea.substr(pos3 + 1, pos4 - pos3 - 1);  // Correo electrónico
            telefono = linea.substr(pos4 + 1, pos5 - pos4 - 1);  // Teléfono
            icon = linea.substr(pos5 + 1); //icono

            if (codigo == codigoCliente) {
                if(correo_escrito==correo){return true;} //valido
            } else 
            {
                if(correo_escrito==correo){return false;}//invalido (hay un correo igual)
            }
        }
        return true;//valido
    }
    
    static bool actualizarCliente(int codigoCliente, const string &nuevoNombre, const string &nuevoCorreo, const string &nuevoTelefono, const string &fecha) {
    ifstream archivo("clientes.txt");
    ofstream archivoTemp("clientes_temp.txt"); // Archivo temporal para guardar los cambios
    if (!archivo.is_open() || !archivoTemp.is_open()) {
        cerr << "No se pudo abrir el archivo" << endl;
        return false;
    }

    string linea;
    int codigo;
    string nombre, correo, telefono, fechaNacimiento, icono;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        int pos4 = linea.find(';', pos3 + 1);
        int pos5 = linea.find(';', pos4 + 1);

        codigo = stoi(linea.substr(0, pos1));  
        nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);  
        fechaNacimiento = linea.substr(pos2 + 1, pos3 - pos2 - 1); 
        correo = linea.substr(pos3 + 1, pos4 - pos3 - 1); 
        telefono = linea.substr(pos4 + 1, pos5 - pos4 - 1);  
        icono = linea.substr(pos5 + 1); 

        // Si encontramos el código del cliente
        if (codigo == codigoCliente) {
            nombre = nuevoNombre;
            correo = nuevoCorreo;
            telefono = nuevoTelefono;
            if(fecha!=""){fechaNacimiento=fecha;}
            encontrado = true;
        }

        archivoTemp << codigo << ";" << nombre << ";" << fechaNacimiento << ";" << correo << ";" << telefono << ";" << icono << endl;
    }

    archivo.close();
    archivoTemp.close();

    if (encontrado) {
        remove("clientes.txt"); // Eliminar archivo original
        rename("clientes_temp.txt", "clientes.txt"); // Renombrar archivo temporal
        return true;
    } else {
        remove("clientes_temp.txt"); // Eliminar archivo temporal si no se encontró el cliente
        cerr << "Cliente no encontrado para actualizar" << endl;
        return false;
    }
}

static void crearCliente(const string &nombre, const string &correo,  const string &telefono, const string &fecha, int &codigoCliente) {

    string icono = to_string(codigoCliente) + ".jpg";

    ofstream archivo("clientes.txt", ios::app);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo clientes.txt" << endl;
        return;
    }

    archivo << codigoCliente << ";" 
            << nombre << ";" 
            << fecha << ";" 
            << correo << ";" 
            << telefono << ";" 
            << icono << "\n"; ;

    archivo.close(); 

    return;
}

    int getCodigoCliente()  { return codigoCliente; }
};
