#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Usuario {
private:
    string nombreUsuario;
    string contrasena;
    int codigoCliente;

public:

    Usuario(string usuario, string password, int codigo)
        : nombreUsuario(usuario), contrasena(password), codigoCliente(codigo) {}

    // Getters
    string getNombreUsuario() {
        return nombreUsuario;
    }

    int getCodigoCliente() {
        return codigoCliente;
    }

    bool verificarCredenciales(string &usuario,  string &contrasena) {
        return (nombreUsuario == usuario && this->contrasena == contrasena);
    }

    void mostrarUsuario() {
        cout << "Usuario: " << nombreUsuario << ", Cliente código: " << codigoCliente << endl;
    }


    static bool verificarLogin(const string &usuario, const string &contrasena, int &codigo) {
        ifstream archivo("usuarios.txt");
        string linea, usuarioFile, contrasenaFile;
        int codigoCliente;

        while (getline(archivo, linea)) {
            int pos1 = linea.find(';');
            int pos2 = linea.find(';', pos1 + 1);

            usuarioFile = linea.substr(0, pos1);
            contrasenaFile = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            codigoCliente = stoi(linea.substr(pos2 + 1));

            // Si el usuario y la contraseña coinciden, el login es correcto
            if (usuarioFile == usuario && contrasenaFile == contrasena) {
                codigo=codigoCliente;
                return true;
            }
        }

        return false;  // Login fallido
    }
};
