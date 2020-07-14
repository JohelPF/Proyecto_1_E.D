#include <iostream>
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
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
