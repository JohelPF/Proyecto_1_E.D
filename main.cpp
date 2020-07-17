
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <curses.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
/*Inicio del las palabras no delimitadoras y sus operaciones*/
typedef struct _Nodelim{
    set<string> tree;
}Nodelim;
Nodelim PalabrasNoDelimitadoras;
bool BuscaNodelim(string word){
    set<string>::iterator it;
    for (it=PalabrasNoDelimitadoras.tree.begin(); it != PalabrasNoDelimitadoras.tree.end(); it++){
        if (*it == word){
            return true;
        }
    }
    return false;
}
void InsertaNodelim(string word){
    PalabrasNoDelimitadoras.tree.insert(word);
}
void RemueveNodelim(string word){
    PalabrasNoDelimitadoras.tree.erase(word);
}
/*-------------------------------------*/

/*Inicio del Separadores y sus operaciones*/
typedef struct _Separadores{
    char separador;
    _Separadores * siguiente = NULL;
}Separadores;
Separadores * primerosep;
void InsertaSep(char separador){
    if (primerosep == NULL){
        primerosep = new Separadores ();
        primerosep->separador = separador;
        return;
    }
    else{
        Separadores *recorrido = primerosep;
        while (true) {
            if (recorrido->separador == separador){
                break;
            }
            else if (recorrido->siguiente == NULL) {
                recorrido->siguiente = new Separadores ();
                recorrido->siguiente->separador = separador;
                break;
            }
            recorrido = recorrido->siguiente;
        }
        return;
    }
}
void RemueveSep(char separador){
    Separadores *recorrido = primerosep;
    Separadores *temp;
    while (true) {
        if (recorrido->separador == separador && recorrido == primerosep){
            primerosep = recorrido->siguiente;
            free(recorrido);
            return;
        }
        else if(recorrido->siguiente->separador == separador){
            temp = recorrido->siguiente;
            recorrido->siguiente = recorrido->siguiente->siguiente;
            free(temp);
            return;
        }
        else if (recorrido->siguiente == NULL) {
            return;
        }
        recorrido = recorrido->siguiente;
    }
    return;
}
bool EsSeparador(char revisar){
    Separadores *recorrido = primerosep;
    while (true) {
        if (recorrido->separador == revisar){
            return true;
        }
        else if (recorrido->siguiente == NULL) {
            return false;
        }
        recorrido = recorrido->siguiente;
    }
}
void SeparadoresActuales(){
    Separadores *recorrido = primerosep;
    string mensaje = "Los separadores actuales son: ";
    string tempmensaje = "'";
    while (true) {
        tempmensaje.push_back(recorrido->separador);
        tempmensaje = tempmensaje + "'";
        mensaje = mensaje + tempmensaje +" ";
        tempmensaje = "'";
        if (recorrido->siguiente == NULL) {
            cout << mensaje << endl;
            return;
        }
        recorrido = recorrido->siguiente;
    }
}
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
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        imprimeHistograma();
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
            }
        }
        imprimeHistograma();
        RetornaHisto();
    }
}
void procesamiento_de_estandar_alpha(int respuesta1, int respuesta2){
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
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        imprimeHistograma();
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
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
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        imprimeHistograma();
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
            }
        }
        imprimeHistograma();
        RetornaHisto();
    }
}
void procesamiento_de_texto_apha(int respuesta1, int respuesta2){
    string texto = lectura_archivo();
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        escritura_archivo();
        RetornaHisto();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
            }
        }
        imprimeHistograma();
        RetornaHisto();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
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
    int resp;
    if (opcion == 0){
        cout << "Salida: '1' para estandar o '0' para archivo de texto" << endl;
        cin >> resp1;
        cout << "Desesa tomar en cuenta mayusculas? '1' para si y '0' para no" << endl;
        cin >> resp2;
        cout << "Desesa utilizar el alfabeto definido e ignorar las demas palabras? '1' para si y '0' para no" << endl;
        cin >> resp;
        if (resp == 0) {
            procesamiento_de_texto(resp1, resp2);
        }
        else{
            procesamiento_de_texto_apha(resp1, resp2);
        }
    }
    else{
        cout << "Salida: '1' para estandar o '0' para archivo de texto" << endl;
        cin >> resp1;
        cout << "Desesa tomar en cuenta mayusculas? '1' para si y '0' para no" << endl;
        cin >> resp2;
        cout << "Desesa utilizar el alfabeto definido e ignorar las demas palabras? '1' para si y '0' para no" << endl;
        cin >> resp;
        if (resp == 0) {
            procesamiento_de_estandar(resp1, resp2);
        } else{
            procesamiento_de_estandar_alpha(resp1, resp2);
        }
    }
}
void InsertarSeparador(){
    char sep;
    SeparadoresActuales();
    cout << "Digite el separador a ser añadido" << endl;
    cin >> sep;
    InsertaSep(sep);
}
void RemoverSeparador(){
    char sep;
    SeparadoresActuales();
    cout << "Digite el separador a ser removido" << endl;
    cin >> sep;
    RemueveSep(sep);
}
void NewNodelim(){
    string palabra;
    cout << "Digite la palabra a ser añadida" << endl;
    cin >> palabra;
    InsertaNodelim(palabra);
}
void RemNodelim(){
    string palabra;
    cout << "Digite la palabra a ser removida" << endl;
    cin >> palabra;
    RemueveNodelim(palabra);
}
int main() {
    char respuesta;
    InsertaSep(' ');
    do {
        cout << "Digite la opcion que desea realizar" << endl;
        cout << "1-Digite para procesar desde la salida estandar" << endl;
        cout << "2-Digite para procesar desde un archivo de texto" << endl;
        cout << "3-Digite para ingresar un separador" << endl;
        cout << "4-Digite para remover un separador" << endl;
        cout << "5-Digite para ingresar una palabra la cual no se va a tomar en cuenta como un separador" << endl;
        cout << "6-Digite para remover una palabra la cual no se va a tomar en cuenta como un separador" << endl;
        cout << "7-Digite para salir" << endl;
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
                InsertarSeparador();
                break;
            case '4':
                RemoverSeparador();
                break;
            case '5':
                NewNodelim();
            case '6':
                RemNodelim();
            case '7':
                cout << "Saliendo gracias!" << endl;
                exit(1);
            default:
                cout << "El numero digitado no corresponde a ninguna opcion" << endl;
                break;
        }
    }while (respuesta != 5);
    return 0;
}