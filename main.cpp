
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <curses.h>
#include <vector>
#include <algorithm>
using namespace std;
/*Inicio del Separadores y sus operaciones*/
typedef struct _Separadores{
    char separador;
    _Separadores * siguiente = NULL;
}Separadores;
/*-------------------------------------*/

/*Inicio del Lexicon y sus operaciones*/
typedef struct _Lexicon{
    unordered_map<string,int> TablaHash;
}Lexicon;
Lexicon raiz;
bool EncontrarPalabra(string palabra){
    unordered_map<string,int>::const_iterator encontro = raiz.TablaHash.find(palabra);
    if (encontro == raiz.TablaHash.end()){
        return false;
    }
    else{
        return true;
    }
}
void DevuelveHash(){
    for (pair<string, int> encontro : raiz.TablaHash) {
        cout << encontro.first << " con " << encontro.second << " ocurrencias" << endl;
    }
    return;
}
void AgregarOcurrencia(string palabra){
    auto puntero = raiz.TablaHash.find(palabra);
    puntero->second = puntero->second+1;
    return;
}
void InsertarPalabra(string palabra){
    raiz.TablaHash.insert({palabra,1});
}
void RemuevePalabra(string palabra){
    raiz.TablaHash.erase(palabra);
}
/*-------------------------------------*/

/*Inicio del Histograma y sus operaciones*/
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
void imprimeHistograma(){
    cout << "\n";
    int cantMax = 0;
    int cantMaxLetras = 0;
    vector<char> palabras;
    int cantidades[200];
    Histograma * recorrido = primero;
    while (true){
        if(recorrido->cantidad > 0){
            if(recorrido->cantidad > cantMax){
                cantMax = recorrido->cantidad;
            }
            palabras.push_back(recorrido->letra);
            cantidades[cantMaxLetras] = recorrido->cantidad;
            cantMaxLetras++;
        }
        if (recorrido->siguiente == NULL){
            break;
        }
        recorrido = recorrido->siguiente;
    }

    for(int i = cantMax + 1; i > 0; --i ){
        cout << i << " |";
        for(int j = 0; j < cantMaxLetras; j++){
            if(cantidades[j] >= i){
                cout << "*";
            }
            cout << "\t";
        }
        cout << "\n";
    }
    cout << "  |";
    sort(begin(palabras), end(palabras));
    for(int f = 0; f < (cantMaxLetras * 8); f++ ){
        cout << "-" ;
    }
    cout << "\n" << "  |";
    for(int h = 0; h < cantMaxLetras; h++){
        cout << palabras.at(h) << "\t" ;
    }
    cout << "\n" << "\n";

}
/*-------------------------------------*/
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
void escritura_archivo(){
    ofstream archivo;
    archivo.open("salida.txt", ios::out);

    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    archivo << "\n";
    int cantMax = 0;
    int cantMaxLetras = 0;
    vector<char> palabras;
    char cantidades[200];
    Histograma * recorrido = primero;
    while (true){
        if(recorrido->cantidad > 0){
            if(recorrido->cantidad > cantMax){
                cantMax = recorrido->cantidad;
            }
            palabras.push_back(recorrido->letra);
            cantidades[cantMaxLetras] = recorrido->cantidad;
            cantMaxLetras++;
        }
        if (recorrido->siguiente == NULL){
            break;
        }
        recorrido = recorrido->siguiente;
    }
    sort(begin(palabras), end(palabras));
    for(int i = cantMax + 1; i > 0; --i ){
        archivo << i << " |";
        for(int j = 0; j < cantMaxLetras; j++){
            if(cantidades[j] >= i){
                archivo << "*";
            }
            archivo << "\t";
        }
        archivo << "\n";
    }
    archivo << "  |";
    for(int f = 0; f < (cantMaxLetras * 8); f++ ){
        archivo << "-" ;
    }
    archivo << "\n" << "  |";
    for(int h = 0; h <= cantMaxLetras; h++){
        archivo << palabras.at(h) << "\t";
    }
    archivo << "\n" << "\n";
}
void procesamiento_de_estandar(int respuesta1, int respuesta2){
    erase();
    string texto;
    int  maxX;
    char ch, entero;

    initscr();			/* Empieza el modo curses		*/
    raw();				/* Line buffering inhabilitado	*/
    keypad(stdscr, TRUE);		/* Los tipo F1 no tiran el programa*/
    maxX= getmaxx(stdscr);
    printw("Digite el texto a ser procesado y digite 1 para terminar\n");
    while(true) {
        ch = getch();       //obtenemos un carácter
        texto.push_back(ch);
        if(ch == '1') {
            texto.pop_back();
            break;
        }
    }
    refresh();
    //Esperamos un input para terminar la ventana
    entero = getch();
    endwin(); //Cerramos la ventana
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        imprimeHistograma();
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        imprimeHistograma();
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
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(tolower(texto[i]));
            }
        }
        imprimeHistograma();
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] != ' ') {
                InsertaHisto(texto[i]);
            }
        }
        imprimeHistograma();
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