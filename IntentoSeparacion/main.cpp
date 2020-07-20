#include <iostream>
#include <sstream>
#include <fstream>
#include <curses.h>
#include <ctime>
#include "Posicion.cpp"
#include "Alfabeto.cpp"
#include "Separadores.cpp"
#include "Lexicon.cpp"
#include "Histograma.cpp"
using namespace std;
double tiempo;

void MenuSalida(){
    string respuesta;
    string palabra;
    string prefijo;
    while (true) {
        cout << "Digite la opcion que desea realizar" << endl;
        cout << "1-Ver Histograma" << endl;
        cout << "2-Ver diccionario de palabras/tokens" << endl;
        cout << "3-Ver diccionario de palabras/tokens con posiciones" << endl;
        cout << "4-Buscar palabra" << endl;
        cout << "5-Buscar prefijo" << endl;
        cout << "6-Ver estadisticas" << endl;
        cout << "7-Regresar al menu pasado" << endl;
        cin >> respuesta;
        if (respuesta == "1")
            imprimeHistograma();
        else if (respuesta == "2")
            DevuelveHash();
        else if (respuesta == "3"){
            DevuelveHashPos();
        }
        else if (respuesta == "4") {
            cout << "Digite la palabra a buscar" << endl;
            cin >> palabra;
            cout << EncPalabra(palabra) << endl;
        }
        else if (respuesta == "5") {
            cout << "Digite el prefijo a buscar" << endl;
            cin >> prefijo;
            EncPrefijo(prefijo,prefijo.size());
        }
        else if (respuesta == "6")
            ;
        else if (respuesta == "7")
            break;
        else{
            cout << "Opcion no valida" << endl;
        }
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
        texto += "\n";
    }
    archivo.close();
    texto.pop_back();
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
    vector<char> cantidades;
    Histograma * recorrido = primero;
    while (true){
        if(recorrido->cantidad > 0){
            if(recorrido->cantidad > cantMax){
                cantMax = recorrido->cantidad;
            }
            palabras.push_back(recorrido->letra);
            cantMaxLetras++;
        }
        if (recorrido->siguiente == NULL){
            break;
        }
        recorrido = recorrido->siguiente;
    }
    sort(begin(palabras), end(palabras));
    for(int i = 0; i < palabras.size(); i++){
        cantidades.push_back(retorna_cantidad(palabras[i]));
    }
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
    for(int h = 0; h < cantMaxLetras; h++){
        archivo << palabras.at(h) << "\t";
    }
    archivo << "\n" << "\n";
    for (pair<string, int> encontro : raiz.TablaHash) {
        archivo << encontro.first << " con " << encontro.second << " ocurrencias" << endl;
        Posicion *recorrido = primpos;
        while (true){
            if (recorrido->palabra == encontro.first){
                for (int i = 0; i<recorrido->posicion.size() ; i++){
                    archivo << "Encontrado en linea: " << recorrido->linea[i] << " en la posicion: " << recorrido->posicion[i] << endl;
                }
                break;
            }
            recorrido = recorrido->siguiente;
        }
    }
    archivo.close();
}
void procesamiento_de_estandar(int respuesta1, int respuesta2){
    erase();
    string texto;
    int  maxX = 0;
    char ch, entero;
    string palabra;
    int linea = 1;
    int posicion = 1;
    int resta = 0;
    int temp;

    initscr();			/* Empieza el modo curses		*/
    raw();				/* Line buffering inhabilitado	*/
    keypad(stdscr, TRUE);		/* Los tipo F1 no tiran el programa*/
    //maxX= getmaxx(stdscr);
    printw("Digite el texto a ser procesado y digite enter para terminar\n");
    while(true) {
        ch = getch();       //obtenemos un carácter
        texto.push_back(ch);
        maxX++;
        if(ch == 10) {
            break;
        }
    }
    //posiciones(texto, maxX);
    refresh();
    //Esperamos un input para terminar la ventana
    //entero = getch();
    endwin(); //Cerramos la ventana
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }

            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        MenuSalida();
    }
}
void procesamiento_de_estandar_alpha(int respuesta1, int respuesta2){
    erase();
    string texto;
    int  maxX;
    char ch, entero;
    string palabra;
    int linea = 1;
    int posicion = 1;
    int resta = 0;
    int temp;

    initscr();			/* Empieza el modo curses		*/
    raw();				/* Line buffering inhabilitado	*/
    keypad(stdscr, TRUE);		/* Los tipo F1 no tiran el programa*/
    maxX= getmaxx(stdscr);
    printw("Digite el texto a ser procesado y digite enter para terminar\n");
    while(true) {
        ch = getch();       //obtenemos un carácter
        texto.push_back(ch);
        if(ch == 10) {
            break;
        }
    }
    refresh();
    //Esperamos un input para terminar la ventana
    //entero = getch();
    endwin(); //Cerramos la ventana
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            if (BuscaNodelim(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        MenuSalida();
    }
}
void procesamiento_de_texto(int respuesta1, int respuesta2){
    string texto = lectura_archivo();
    cout << texto << endl;
    string palabra;
    int linea = 1;
    int posicion = 1;
    int resta = 0;
    int temp;
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else{
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
        }
        MenuSalida();
    }
}
void procesamiento_de_texto_apha(int respuesta1, int respuesta2){
    string texto = lectura_archivo();
    string palabra;
    int linea = 1;
    int posicion = 1;
    int resta = 0;
    int temp;
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        escritura_archivo();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
                resta += 1;
                posicion +=1;
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (texto[i] == 10){
                temp = posicion - resta;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
                linea+=1;
                posicion = 1;
                resta = 0;
            }
            else if (BuscaNodelim(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else if(palabra != ""){
                temp = posicion - resta;
                resta = 0;
                posicion +=1;
                Determinar(palabra);
                DecidePos(palabra,linea,temp);
                palabra = "";
            }
            else{
                posicion += 1;
            }
        }
        MenuSalida();
    }
}

void menu_opciones(int opcion){
    unsigned int t0, t1;
    t0 = clock();
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
    t1 = clock();
    tiempo = (double(t1-t0)/CLOCKS_PER_SEC);
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
    char palabra;
    cout << "Digite la letra a ser añadida" << endl;
    cin >> palabra;
    InsertaNodelim(palabra);
}
void RemNodelim(){
    char palabra;
    cout << "Digite la letra a ser removida" << endl;
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
        cout << "5-Digite para ingresar una letra al alfabeto" << endl;
        cout << "6-Digite para remover una letra del alfabeto" << endl;
        cout << "7-Digite para salir" << endl;
        cin >> respuesta;
        string palabra;
        string oracion;
        switch (respuesta) {
            case '1':
                VaciaHisto();
                EliminaHash();
                EliminaPos();
                menu_opciones(1);;
                break;
            case '2':
                VaciaHisto();
                EliminaHash();
                EliminaPos();
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
                break;
            case '6':
                RemNodelim();
                break;
            case '7':
                cout << tiempo << endl;
                cout << "Saliendo gracias!" << endl;
                exit(1);
            default:
                cout << "El numero digitado no corresponde a ninguna opcion" << endl;
                break;
        }
    }while (respuesta != 7);
    return 0;
}