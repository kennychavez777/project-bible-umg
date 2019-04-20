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
string path = "C:\\Users\\usuario\\Documents\\Universidad\\Progra 1\\Project2\\database\\"; // Declarramos una variable global con la ruta de la base de datos

int getStatusDB(string path){ // Declaramos una función que nos retornara un entero con la cantidad de archivos que hay en nuestra carpeta de base de datos
    DIR *dir; // Declaramos un puntero
    struct dirent *ent; // Declaramos otro puntero de tipo struct
    int count = -2; // Declaramos un contador en -2, para no tomar en cuenta "." y ".." que vienen por defecto en el sistema de archivos

    if ((dir = opendir (path.c_str())) != NULL) { // Verificamos si hay archivos dentro del directorio
        while ((ent = readdir (dir)) != NULL) { // Recorremos todos los archivos que existan
            count++; // Sumamos uno cada vez que se encuentre archivo/directorio nuevo
        }
        closedir (dir); // Cerramos el directorio
    }

    return count; // Retornamos el conteo de archivos que existen
}

void showMenu(){ // Declaramos una funcion que muestra el menu principal
    string dbStatus = "No disponible"; // Declaramos el estado de nuestra base de datos
    int quantityFiles = getStatusDB(path); // Guardamos la cantidad de archivos que tenemos en el directorio

    if(quantityFiles > 0){ // Si la cantidad de archivos es mayor a 0, entonces el estado será disponible
        dbStatus = "Disponible"; // Cambiamos el estado a Disponible
    }

    system("CLS"); // Limpiamos pantalla
    //Mostramos toda la informacion necesaria en pantalla, junto con el menu
    cout << "Estado Base de Datos: " << dbStatus << endl;
    cout << "Cantidad de archivos: " << quantityFiles << endl;
    cout << "Ruta especifica (DB): " << path << endl << endl;
    cout << "--------------MENU--------------" << endl;
    cout << "1. Leer o cargar archivos" << endl;
    cout << "2. Buscar" << endl;
    cout << "3. Terminar sesion" << endl;
    cout << "\nOpcion: ";
}

void showMenuAdmin(){ // Declaramos otra funcion para mostrar un menu secundario
    system ("CLS"); // Limpiamos pantalla
    // Mostramos el menu
    cout << "Administracion de archivos" << endl; //
    cout << "1. Crear archivo" << endl;
    cout << "2. Leer archivo" << endl;

    cout << "\nOpcion: ";
}

void createFile(){ // Declaramos una funcion crear archivo
    string filename, text, completeText; // Declaramos todas las variables que utilizaremos en el flujo de la funcion

    system("CLS"); // Limpiamos pantalla
    cin.ignore(); // Sirve para que podamos utilizar getline

    // Solicitamos los datos correspondientes para la creacion de un archivo
    cout << "Instrucciones: Para guardar y terminar el proceso de introduccion del texto, escribir en pantalla !wq" << endl;
    cout << "Crear archivo" << endl;
    cout << "Nombre: ";
    cin >> filename;
    cout << "Texto: ";

    while(getline(std::cin, text)){ // Recorremos el texto ingresado
        if(text == "!wq"){ // Verificamos que en el texto no se haya incluido "!wq", que simula la el "guardar y cerrar" de VIM/VI en Linux
            break; // Si esto sucede, terminamos con el recorrido
        }else{
            completeText = completeText + text; // De lo contrario el texto se seguira guardando.
        }
        completeText = completeText + "\n"; // Se ira tomando saltos de linea
    }

    string directory = path + filename; // Seteamos la direccion completa de la base de datos

    std::ofstream newFile (directory.c_str()); // Abrimos un archivo
    newFile << completeText; // Guardamos el texto completo en el archivo
    newFile.close(); // Cerramos el archivo

    cout << "\n\n=> Archivo creado en: " << path << endl; // Muestra en donde fue creao el archivo
    Sleep(2000); // Esperamos 2 segundos para volver a la pantalla principal
}

void readDirectory(){ // Creamos una funcion para leer archivos
    string filename, directory, line; // Declaramos todas las variables que se utilizaran en todo el flujo de la funcion

    system("CLS"); // Limpiamos pantalla

    // Pedimos todos los datos correspondientes
    cout << "Leer archivos" << endl;
    cout << "Archivo: ";
    cin >> filename;

    directory = path + filename; // Declaramos la ruta

    ifstream file(directory.c_str()); // Abrimos el archivo

    while(getline(file, line)){ // Recorremos el archivo linea por linea
        cout << line << endl; // imprimimos la linea
    }

    cout << "\n\n"; // Imprimimos 2 saltos de linea
    system("pause"); // Pausamos el programa
}

void administrateFiles(){ // Creamos una funcion para administrar archivos
    int opt; // Declaramos una variable para determinar opciones
    showMenuAdmin(); // Mostamos el menu

    cin >> opt; // Pedimos la opcion

    switch (opt) { // La opcion se evalua
        case 1:
            createFile(); // Ejecutamos la funcion para crear un archivo
            break;
        case 2:
            readDirectory(); // Ejecutamos la funcion para leer un archivo
            break;
        default:
            cout << "\nError: Opcion invalida\n"; // De lo contrario la opcion sera invalida
    }
}

void searchInDatabase(){ // Declaramos una funcion que realizara una busqueda mediante capitulo y versiculo
    string book, chapter, verse, filename, line, completeText, nextV, nextChap; // Declaramos todas las variables para este flujo
    int nextVerse = 0, nextChapter = 0; // Declaramos mas variables que nos serviran para el flujo de la funcion

    system("CLS"); // Limpiamos pantalla
    // Solicitamos al usuario todo lo necesario
    cout << "Buscar en base de datos" << endl;
    cout << "Libro: ";
    cin >> book;
    cout << "Capitulo: ";
    cin >> chapter;
    cout << "Versiculo: ";
    cin >> verse;

    istringstream(chapter) >> nextChapter; // Guaramos el capitulo en una variable int
    nextChapter++; // Sumamos 1 al capitulo
    istringstream(verse) >> nextVerse; // Guardamos el versiculo en una variable int
    nextVerse++; // Sumamos 1 al versiculo

    filename = path + book + ".txt"; // Concatenamos para abrir el archivo correcto
    ifstream file(filename.c_str()); // Declaramos la variable file, que sera la encargada de administrar el archivo

    if(file.is_open()){ // Abrimos el archivo
        while(getline(file, line)){ // Recorremos el archivo
            completeText = completeText + line; // Guardamos todo en una variable string
        }

        string delimiter = chapter + ":" + verse; // Declaramos el primer delimitador con el capitulo y el versiculo
        int find_ = completeText.find(delimiter); // Usamos la funcion find, para saber en que numero de caracter comienza

        if(find_ >= 0){ // Verificamos que find, haya encontrado algo
            completeText.erase(0, find_); // Eliminamos desde el caracter 0 hasta la el numero de caracter que haya devuelto find

            std::stringstream ss; // Declaramos una variable stringstream
            ss << nextVerse; // Guardamos la variable entera en la variable ss
            nextV = ss.str(); // La convertimos a string nuevamente
            string delimiter2 = chapter + ":" +  nextV; // Declaramos el delimitador 2

            int find2_ = completeText.find(delimiter2); // Hacemos uso de la funcion find y el delimitador 2 para encontrar coincidencias

            if(find2_ > 0){ // Evaluamos si se encuentra algo
                completeText.erase(find2_, completeText.length()); // Eliminamos el resto de la informacion
            }

            std::stringstream ss2; // Declaramos otra variable stringstream
            ss2 << nextChapter; // Guardamos la variable entera en la variable ss2
            nextChap = ss2.str(); // La convertimos a string nuevamente
            string delimiter3 = nextChap + ":1"; // Declaramos el delimitador 3

            int find3_ = completeText.find(delimiter3); // Hacemos uso de la funcion find y el delimitador 3 para encontrar coincidencias

            if(find3_ > 0){ // Evaluamos si se encuentra algo
                completeText.erase(find3_, completeText.length()); // Eliminamos el resto de la informacion
            }

            cout << "\nResultado: \n" << completeText << endl; // Imprimimos todos los resultados
        }else {
            cout << "\nNo se encontro el capitulo requerido." << endl; // Mostramos este mensaje si no se encontro alguna coincidencia
        }

        cout << "\n"; // Imprimimos un salto de linea
        system("pause"); // Detenemos el programa
    }else{
        cout << "\nERROR: No se ha encontrado el libro solicitado\n"; // Mostramos que no se ha encontrado el libro solicitado
        system("pause"); // Detenemos el programa
    }
}

int main() { // Declaracion del metodo principal
    int option; // Declaramos una variable opcion para el flujo del programa

    while(option != 3){ // Se recorre hasta que la opcion sea 3
        showMenu(); // Mostramos el menu
        cin >> option; // Guardamos la opcion en una variable

        switch (option){ // Verificamos la opcion
            case 1:
                administrateFiles(); // Hacemos uso de la funcion para administrar archivos
                break;
            case 2:
                searchInDatabase(); // Hacemos uso de la funcion de busqueda en base de datos
                break;
            case 3:
                return 0; // Terminamos la ejecucion de la funcion
                break;
            default:
                cout << "\n\nError: La opcion elegida no existe\n\n"; // De lo contrario saldra este error
        }
    }

    return 0;
}
