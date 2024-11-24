#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Usuario {
private:
    string nombreUsuario;
    string contrasena;
    int codigoCliente;
    bool bloqueo;

public:

    Usuario(string usuario, string password, int codigo, bool bloqueo)
        : nombreUsuario(usuario), contrasena(password), codigoCliente(codigo), bloqueo(false) {}


    static bool verificarLogin(const string &usuario, const string &contrasena, int &codigo) 
    {
        ifstream archivo("usuarios.txt");
        string linea, usuarioFile, contrasenaFile;
        int codigoCliente;
        bool bloqueo;

        while (getline(archivo, linea)) 
        {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);

            usuarioFile = linea.substr(0, pos1);                         
            contrasenaFile = linea.substr(pos1 + 1, pos2 - pos1 - 1);    
            codigoCliente = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1)); 
            bloqueo = linea.substr(pos3 + 1) == "1";  

            if (usuarioFile == usuario) 
            {
                if (bloqueo) {
                    outtextxy(870, 605, (char*)"Usuario Bloqueado");
                    return false;
                }
                if (contrasenaFile == contrasena) {
                    codigo = codigoCliente;
                    return true; 
                } else {
                    outtextxy(870, 605, (char*)"Credenciales incorrectas");
                    return false;
                }
            }
        }
        outtextxy(870, 605, (char*)"Usuario no encontrado");
        return false;
    }

    static bool obtenerUsuarioYClave(int codigo, char* usuario, char* clave, bool &bloqueoCta) {
        ifstream archivo("usuarios.txt");
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
            return false;
        }

        string linea, usuarioFile, claveFile;
        int codigoFile;
        bool bloqueo;
        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);

            usuarioFile = linea.substr(0, pos1);
            claveFile = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            codigoFile = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            bloqueo = linea.substr(pos3 + 1) == "1";  

            if (codigoFile == codigo) {
                strcpy(usuario, usuarioFile.c_str());
                strcpy(clave, claveFile.c_str());
                bloqueoCta = bloqueo;
                archivo.close();
                return true; 
            }
        }

        archivo.close();
        cerr << "Código de cliente no encontrado." << endl;
        return false;
    }

    static bool VerificarUsuario(int codigo, char* usuario) {
        ifstream archivo("usuarios.txt");
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
            return false;
        }

        string linea, usuarioFile, claveFile;
        int codigoFile;
        bool bloqueo;
        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);

            usuarioFile = linea.substr(0, pos1);
            claveFile = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            codigoFile = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            bloqueo = linea.substr(pos3 + 1) == "1";  

            if (codigoFile == codigo) {
                if(usuario==usuarioFile){return true; }//valido
            } else 
            {
                if(usuario==usuarioFile){return false; }//invalido
            }
        }

        archivo.close();
        return true;
    }

static bool actualizarUsuario(int codigo, const string &nuevoUsuario, const string &nuevaClave, bool& bloqueoCta) {
    ifstream archivo("usuarios.txt");
    ofstream archivoTemp("usuarios_temp.txt"); // Archivo temporal para escribir los cambios
    if (!archivo.is_open() || !archivoTemp.is_open()) {
        cerr << "No se pudo abrir el archivo" << endl;
        return false;
    }

    string linea, usuarioFile, claveFile;
    int codigoFile;
    bool bloqueo;
    bool encontrado = false;

    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);

        usuarioFile = linea.substr(0, pos1);
        claveFile = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        codigoFile = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
        bloqueo = linea.substr(pos3 + 1) == "1";

        if (codigoFile == codigo) {
             cout << "Usuario encontrado: " << usuarioFile << endl;
            usuarioFile = nuevoUsuario;  // Cambiar usuario
            claveFile = nuevaClave;      // Cambiar clave
            bloqueo=bloqueoCta;
            encontrado = true;
        }

        archivoTemp << usuarioFile << ";" << claveFile << ";" << codigoFile << ";" << (bloqueo ? "1" : "0") << endl;
    }

    archivo.close();
    archivoTemp.close();

    if (encontrado) {
        remove("usuarios.txt"); // Eliminar archivo original
        rename("usuarios_temp.txt", "usuarios.txt"); // Renombrar archivo temporal
        return true;
    } else {
        remove("usuarios_temp.txt"); // Eliminar archivo temporal si no se encontro el usuario
        cerr << "Usuario no encontrado para actualizar" << endl;
        return false;
    }
}

static void mostrarTodosLosCodigos() {
    const int maxUsuarios = 100;
    int codigos[maxUsuarios];

    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
        return;
    }

    string linea;
    int codigoCliente;
    int index = 0;

    while (getline(archivo, linea) && index < maxUsuarios) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);
        codigoCliente = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
        if(codigoCliente!=30737409)
        {
            codigos[index] = codigoCliente;
            index++;
        }

    }
    archivo.close();

    int startX = 350;
    int startY = 100;
    int offsetX = 100;
    int offsetY = 50;
    int limiteColumnas = 14;

    int x = startX;
    int y = startY;
    int codigosMostrados = 0;

    for (int i = 0; i < index; ++i) {
        char strCodigo[50];
        itoa(codigos[i], strCodigo, 10);

        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(8, 0, 2);
        outtextxy(x, y, strCodigo);

        codigosMostrados++;
        if (codigosMostrados % limiteColumnas == 0) {
            x = startX;  
            y += offsetY;  
        } else {
            x += offsetX;  
        }
    }
}

static int generarCodigo() {
        srand(time(0));
        int codigo;
        bool existe;
        do {
            existe = false;
            codigo = rand() % 9000 + 1000; // Genera un número entre 1000 y 9999

            // Verificar si el código ya existe en el archivo
            ifstream archivo("usuario.txt");
            int codigoArchivo;
            string linea;
             while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);
            codigoArchivo = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            if (codigoArchivo == codigo) {
                existe = true;
                break;
            }
        }
        archivo.close();
    } while (existe);
    return codigo;
}

static int crearUsuario(const string &usuario, const string &clave) {
        int codigo = generarCodigo();
        
        ofstream archivo("usuarios.txt", ios::app);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
            return false;
        }

        archivo << usuario << ";" << clave << ";" << codigo << ";0\n";

        archivo.close();
        return codigo;
    }

static bool existeCodigo(int codigo) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
        return false;  
    }

    string linea;
    int codigoCliente;

    while (getline(archivo, linea)) {
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        int pos3 = linea.find(';', pos2 + 1);

        codigoCliente = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));

        if (codigoCliente == codigo) {
            archivo.close();
            return true;  // El código existe
        }
    }

    archivo.close();
    return false;  // El código no existe
}

 static bool agregarNotificacion(int codigoUsuario) {
        if (existeNotificacion(codigoUsuario)) {
            cerr << "Ya existe una notificación pendiente para este usuario." << endl;
            return false;
        }

        ofstream archivo("notificaciones.txt", ios::app);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo notificaciones.txt" << endl;
            return false;
        }
        archivo << codigoUsuario << ";pendiente\n"; 
        archivo.close();
        cout << "Notificación agregada con éxito para el usuario " << codigoUsuario << endl;
        return true;
    }

static void mostrarNotificaciones() {
    ifstream archivo("notificaciones.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo notificaciones.txt" << endl;
        return;
    }

    string linea;
    int xStart = 350;  
    int yStart = 265; 
    int offsetX = 500; 
    int offsetY = 30;  
    int columnas = 2;   

    int x = xStart, y = yStart;
    int contador = 0;

    while (getline(archivo, linea)) {
        int pos = linea.find(';');
        int codigo = stoi(linea.substr(0, pos));
        string estado = linea.substr(pos + 1);

        // Mostrar en pantalla
        char buffer[100];
        sprintf(buffer, "Usuario %d - Estado: %s", codigo, estado.c_str());

        outtextxy(x, y, buffer);

        contador++;
        if (contador % columnas == 0) {
            x = xStart;
            y += offsetY;
        } else {
            x += offsetX;
        }
    }

    archivo.close();
}

static bool eliminarNotificacion(int codigoUsuario) {
        ifstream archivo("notificaciones.txt");
        ofstream archivoTemp("notificaciones_temp.txt");

        if (!archivo.is_open() || !archivoTemp.is_open()) {
            cerr << "No se pudo abrir el archivo" << endl;
            return false;
        }

        string linea;
        bool encontrado = false;
        while (getline(archivo, linea)) {
            int pos = linea.find(';');
            int codigo = stoi(linea.substr(0, pos));
            string estado = linea.substr(pos + 1);

            if (codigo == codigoUsuario && estado == "pendiente") {
                encontrado = true;  
                continue; 
            }
            archivoTemp << linea << endl;  
        }

        archivo.close();
        archivoTemp.close();

        if (encontrado) {
            remove("notificaciones.txt");  
            rename("notificaciones_temp.txt", "notificaciones.txt"); 
            return true;
        } else {
            remove("notificaciones_temp.txt");  
            return false;
        }
    }

static bool existeNotificacion(int codigoUsuario) {
        ifstream archivo("notificaciones.txt");
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo notificaciones.txt" << endl;
            return false;
        }

        string linea;
        while (getline(archivo, linea)) {
            int pos = linea.find(';');
            int codigo = stoi(linea.substr(0, pos));
            string estado = linea.substr(pos + 1);

            if (codigo == codigoUsuario && estado == "pendiente") {
                archivo.close();
                return true;  
            }
        }

        archivo.close();
        return false;  
    }

};



