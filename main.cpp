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
string completeVerse = "";

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
        cout << line << endl;
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

bool validateVerse(string line, string chapter, string verse){
    /*string text, chapE, versE;
    bool status = false, statusChapter = false;

    size_t pos = 0;
    std::string token;
    std::string delimiter = chapter + ":" + verse;

    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        chapE = chapE + token;
        cout << "chapE: " << chapE << endl;
        line.erase(0, pos + delimiter.length());
    }

    std::cout << line << std::endl;

    string::iterator si1;
    for(si1 = line.begin() ; si1 < line.end(); si1++){
        cout << *si1 << " ";

        try{
            int i = std::stoi(s);
            chapE = chapE + *si1;

            if(statusChapter){
                if(chapE == chapter){
                    status = true;
                }else{
                    statusChapter = false;
                }
            }
        }
        catch (std::invalid_argument const &e){
            if(*sil == ':'){
                statusChapter = false
            }
        }
    }*/

    //return status;
}

void searchInDatabase(){
    string book, chapter, verse, filename, line, completeText, nextV, nextChap;
    int nextVerse = 0, nextChapter;

    system("CLS");
    cout << "Buscar en base de datos" << endl;
    cout << "Libro: ";
    cin >> book;
    cout << "Capitulo: ";
    cin >> chapter;
    cout << "Versiculo: ";
    cin >> verse;

    istringstream(chapter) >> nextChapter;
    nextChapter++;
    istringstream(verse) >> nextVerse;
    nextVerse++;

    filename = path + book + ".txt";
    ifstream file(filename.c_str());

    if(file.is_open()){
        while(getline(file, line)){
            //validateVerse(line, chapter, verse);
            completeText = completeText + line;
        }

        string delimiter = chapter + ":" + verse;
        int find_ = completeText.find(delimiter);

        if(find_ >= 0){
            completeText.erase(0, find_);

            std::stringstream ss;
            ss << nextVerse;
            nextV = ss.str();
            string delimiter2 = chapter + ":" +  nextV;

            int find2_ = completeText.find(delimiter2);

            if(find2_ > 0){
                completeText.erase(find2_, completeText.length());
            }

            std::stringstream ss2;
            ss2 << nextChapter;
            nextChap = ss2.str();
            string delimiter3 = nextChap + ":1";

            int find3_ = completeText.find(delimiter3);

            if(find3_ > 0){
                completeText.erase(find3_, completeText.length());
            }

            cout << "\nResultado: \n" << completeText << endl;
        }else {
            cout << "\nNo se encontro el capitulo requerido." << endl;
        }

        cout << "\n";
        system("pause");
    }else{
        cout << "\nERROR: No se ha encontrado el libro solicitado\n";
        system("pause");
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
                searchInDatabase();
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
