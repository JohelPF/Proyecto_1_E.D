#include <iostream>
#include <vector>
#include <algorithm>
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


