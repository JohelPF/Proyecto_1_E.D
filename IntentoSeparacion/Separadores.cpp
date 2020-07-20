#include <iostream>
using namespace std;
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

