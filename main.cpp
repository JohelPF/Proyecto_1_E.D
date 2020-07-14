#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
typedef struct _Histograma{
    int cantidad;
    char letra;
    _Histograma * siguiente = NULL;
}Histograma;
Histograma * primero;
void InsertaHisto(char letra){
    if (primero == NULL){
        primero = new Histograma ();
        primero->letra = letra;
        primero->cantidad = 1;
        return;
    }
    else{
        Histograma *recorrido = primero;
        while (true) {
            if (recorrido->letra == letra){
                recorrido->cantidad+=1;
                break;
            }
            else if (recorrido->siguiente == NULL) {
                recorrido->siguiente = new Histograma ();
                recorrido->siguiente->letra = letra;
                recorrido->siguiente->cantidad = 1;
                break;
            }
            recorrido = recorrido->siguiente;
        }
        return;
    }
}
void RetornaHisto(){
    Histograma * recorrido = primero;
    while (true){
        cout << "La letra " << recorrido->letra << " tiene " << recorrido->cantidad <<" ocurrencias"<< endl;
        if (recorrido->siguiente == NULL){
            break;
        }
        recorrido = recorrido->siguiente;
    }
    return;
}
void VaciaHisto(){
    if (primero != NULL) {
        Histograma *recorrido = primero;
        Histograma *temp;
        while (true) {
            if (recorrido->siguiente == NULL) {
                free(recorrido);
                primero = NULL;
                break;
            }
            temp = recorrido->siguiente;
            recorrido->siguiente = recorrido->siguiente->siguiente;
            free(temp);
        }
    }
    else{
        return;
    }
}
string lectura_archivo(){
    ifstream archivo;
    string texto;
    string letra1;
    archivo.open("input_proyecto_1.txt", ios::in);
    if(archivo.fail()){
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    while(!archivo.eof()){
        getline(archivo, letra1);
        texto += letra1;
    }
    archivo.close();
    return texto;
}
void procesamiento_de_estandar(int respuesta1, int respuesta2){
    string texto;
    cout << "Digite el texto a ser procesado" << endl;
    cin >> noskipws >> texto;
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        RetornaHisto();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        RetornaHisto();
    }
}
void procesamiento_de_texto(int respuesta1, int respuesta2){
    string texto = lectura_archivo();
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        RetornaHisto();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        RetornaHisto();
    }
}
void menu_opciones(int opcion){
    int resp1;
    int resp2;
    if (opcion == 0){
        cout << "Salida: '1' para estandar o '0' para archivo de texto" << endl;
        cin >> resp1;
        cout << "Desesa tomar en cuenta mayusculas? '1' para si y '0' para no" << endl;
        cin >> resp2;
        procesamiento_de_texto(resp1,resp2);
    }
    else{
        cout << "Salida: '1' para estandar o '0' para archivo de texto" << endl;
        cin >> resp1;
        cout << "Desesa tomar en cuenta mayusculas? '1' para si y '0' para no" << endl;
        cin >> resp2;
        procesamiento_de_estandar(resp1,resp2);
    }
}
int main() {
    char respuesta;
    do {
        cout << "Digite la opcion que desea realizar" << endl;
        cout << "1-Digite para procesar desde la salida estandar" << endl;
        cout << "2-Digite para procesar desde un archivo de texto" << endl;
        cout << "3-Digite para salir" << endl;
        cin >> respuesta;
        string palabra;
        string oracion;
        switch (respuesta) {
            case '1':
                VaciaHisto();
                menu_opciones(1);;
                break;
            case '2':
                VaciaHisto();
                menu_opciones(0);
                break;
            case '3':
                cout << "Saliendo gracias!" << endl;
                exit(1);
            default:
                cout << "El numero digitado no corresponde a ninguna opcion" << endl;
                break;
        }
    }while (respuesta != 5);
    return 0;
}
