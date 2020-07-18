
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <curses.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
using namespace std;
double tiempo;

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
void Determinar(string palabra){
    if(EncontrarPalabra(palabra)){
        AgregarOcurrencia(palabra);
    }
    else{
        InsertarPalabra(palabra);
    }
}
string EncPalabra(string palabra){
    unordered_map<string,int>::const_iterator encontro = raiz.TablaHash.find(palabra);
    if (encontro == raiz.TablaHash.end()){
        return "Esta palabra no se encuentra";
    }
    else{
        return encontro->first + " con " + to_string(encontro->second) + " ocurrencias" + '\n';
    }
}
void EncPrefijo(string prefijo, int tamanno){
    string pal;
    for (pair<string, int> encontro : raiz.TablaHash) {
        for(int i = 0; i < tamanno; i++){
            pal.push_back(encontro.first[i]);
        }
        if (pal == prefijo) {
            cout << encontro.first << " con " << encontro.second << " ocurrencias" << endl;
        }
        pal = "";
    }
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

int retorna_cantidad(char letra){
    Histograma *recorrido = primero;
    while(true){
        if(recorrido->letra == letra){
            return recorrido->cantidad;
        }
        if(recorrido->siguiente == NULL){
            return 0;
        }
        recorrido = recorrido->siguiente;
    }
}

void imprimeHistograma(){
    cout << "\n";
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

    for(int f = 0; f < (cantMaxLetras * 8); f++ ){
        cout << "-" ;
    }
    cout << "\n" << "  |";
    for(int h = 0; h < cantMaxLetras; h++){
        cout << palabras.at(h) << "\t" ;
    }
    cout << "\n" << "\n";

}
/*void posiciones(){
    string palabra;
    int posicion;
    for(int i = 0; i < max; i++){
        if(not EsSeparador(texto[i])){
            palabra.push_back(texto[i]);
        }else{
            posicion = i - (palabra.size() - 1);
            palabra = "";
        }
    }
}*/
/*-------------------------------------*/
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
            DevuelveHash();
            //posiciones();
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
    archivo.close();
}void posiciones_Archivo(){
    string texto = lectura_archivo();
}

void procesamiento_de_estandar(int respuesta1, int respuesta2){
    erase();
    string texto;
    int  maxX = 0;
    char ch, entero;
    string palabra;

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
            texto.pop_back();
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
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(texto[i]);
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(texto[i]);
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                Determinar(palabra);
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

    initscr();			/* Empieza el modo curses		*/
    raw();				/* Line buffering inhabilitado	*/
    keypad(stdscr, TRUE);		/* Los tipo F1 no tiran el programa*/
    maxX= getmaxx(stdscr);
    printw("Digite el texto a ser procesado y digite enter para terminar\n");
    while(true) {
        ch = getch();       //obtenemos un carácter
        texto.push_back(ch);
        if(ch == 10) {
            texto.pop_back();
            break;
        }
    }
    refresh();
    //Esperamos un input para terminar la ventana
    //entero = getch();
    endwin(); //Cerramos la ventana
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        MenuSalida();
    }
}
void procesamiento_de_texto(int respuesta1, int respuesta2){
    string texto = lectura_archivo();
    string palabra;
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                Determinar(palabra);
                palabra = "";
            }
        }
        MenuSalida();
    }
}
void procesamiento_de_texto_apha(int respuesta1, int respuesta2){
    string texto = lectura_archivo();
    string palabra;
    if (respuesta1 == 0 && respuesta2 == 1){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 == 0 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        escritura_archivo();
        MenuSalida();
    }
    else if (respuesta1 ==1 && respuesta2 == 0){
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(tolower(texto[i]));
                palabra.push_back(tolower(texto[i]));
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
            }
        }
        MenuSalida();
    } else{
        for (int i = 0; i<texto.size(); i++){
            if (not EsSeparador(texto[i])) {
                InsertaHisto(texto[i]);
                palabra.push_back(texto[i]);
            }
            else{
                if(BuscaNodelim(palabra)){
                    Determinar(palabra);
                }
                palabra = "";
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