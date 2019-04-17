/*
    Author: Kenny Chavez
    Versión: 0.0.1
    Description: Read and generate files of biblie
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

using namespace std;
string path = "C:\\Users\\usuario\\Documents\\Universidad\\Progra 1\\Project2\\database\\";

int getStatusDB(string path){
    DIR *dir;
    struct dirent *ent;
    int count = -2;

    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            count++;
        }
        closedir (dir);
    }

    return count;
}

void showMenu(){
    string dbStatus = "No disponible";
    int quantityFiles = getStatusDB(path);

    if(quantityFiles > 0){
        dbStatus = "Disponible";
    }

    system("CLS");
    cout << "Estado Base de Datos: " << dbStatus << endl;
    cout << "Cantidad de archivos: " << quantityFiles << endl;
    cout << "Ruta especifica (DB): " << path << endl << endl;
    cout << "--------------MENU--------------" << endl;
    cout << "1. Leer o cargar archivos" << endl;
    cout << "2. Buscar" << endl;
    cout << "3. Terminar sesion" << endl;
    cout << "\nOpcion: ";
}

void showMenuAdmin(){
    system ("CLS");
    cout << "Administracion de archivos" << endl;
    cout << "1. Crear archivo" << endl;
    cout << "2. Leer archivo" << endl;

    cout << "\nOpcion: ";
}

void createFile(){
    string filename, text, completeText;

    system("CLS");
    cin.ignore();

    cout << "Crear archivo" << endl;
    cout << "Nombre: ";
    cin >> filename;
    cout << "Texto: ";

    while(getline(std::cin, text)){
        if(text == "!wq"){
            break;
        }else{
            completeText = completeText + text;
        }
        completeText = completeText + "\n";
    }

    string directory = path + filename;

    std::ofstream newFile (directory.c_str());
    newFile << completeText;
    newFile.close();

    cout << "\n\n=> Archivo creado en: " << path << endl;
    Sleep(2000);
}

void readDirectory(){
    string filename, directory, line;

    system("CLS");
    cout << "Leer archivos" << endl;
    cout << "Archivo: ";
    cin >> filename;

    directory = path + filename;

    ifstream file(directory.c_str());

    while(getline(file, line)){
        cout << line;
    }

    Sleep(7000);
}

void administrateFiles(){
    int opt;
    showMenuAdmin();

    cin >> opt;

    switch (opt) {
        case 1:
            createFile();
            break;
        case 2:
            readDirectory();
            break;
        default:
            cout << "\nError: Opcion invalida\n";
    }
}

int main() {
    int option;

    while(option != 3){
        showMenu();
        cin >> option;

        switch (option){
            case 1:
                administrateFiles();
                break;
            case 2:
                cout << "Buscar";
                break;
            case 3:
                return 0;
                break;
            default:
                cout << "La opcion elegida no existe";
        }
    }

    return 0;
}
