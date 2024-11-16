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
        : nombreUsuario(usuario), contrasena(password), codigoCliente(codigo), bloqueo(NULL) {}


    static bool verificarLogin(const string &usuario, const string &contrasena, int &codigo) {
        ifstream archivo("usuarios.txt");
        string linea, usuarioFile, contrasenaFile;
        int codigoCliente;
        bool bloqueo;

        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);
            int pos3 = linea.find(';', pos2 + 1);

            usuarioFile = linea.substr(0, pos1);                         
            contrasenaFile = linea.substr(pos1 + 1, pos2 - pos1 - 1);    
            codigoCliente = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1)); 
            bloqueo = linea.substr(pos3 + 1) == "1";  

            // Si el usuario y la contraseña coinciden, el login es correcto
            if (usuarioFile == usuario && contrasenaFile == contrasena && !bloqueo) {
                codigo=codigoCliente;
                return true;
            }
        }
        if(bloqueo){outtextxy(870, 605, (char*)"Usuario Bloqueado"); return false;}
        else{outtextxy(870, 605, (char*)"Credenciales incorrectas"); return false;}
    }
};
