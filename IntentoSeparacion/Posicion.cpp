#include <iostream>
#include <vector>
using namespace std;
typedef struct _Posicion{
    string palabra;
    vector<int> linea;
    vector<int> posicion;
    _Posicion *siguiente = NULL;
}Posicion;
Posicion *primpos = NULL;
bool EnPosicion(string palabra){
    Posicion *recorrido = primpos;
    while (true){
        if (recorrido == NULL){
            return false;
        }
        else if (recorrido->palabra == palabra){
            return true;
        }

        recorrido = recorrido->siguiente;
    }
}
void InsteraPos(int linea,int posicion,string palabra){
    if (primpos == NULL){
        primpos = new Posicion ();
        primpos->palabra = palabra;
        primpos->linea.push_back(linea);
        primpos->posicion.push_back(posicion);
        return ;
    } else{
        Posicion *recorrido = primpos;
        while (true){
            if (recorrido->siguiente == NULL){
                recorrido->siguiente = new Posicion ();
                recorrido->siguiente->palabra = palabra;
                recorrido->siguiente->posicion.push_back( posicion);
                recorrido->siguiente->linea.push_back(linea);
                return ;
            }

            recorrido = recorrido->siguiente;
        }
    }
}
void InsertaNuevaPos(string palabra,int linea,int posicion){
    Posicion *recorrido = primpos;
    while (true){
        if (recorrido->palabra == palabra){
            recorrido->linea.push_back(linea);
            recorrido->posicion.push_back(posicion);
            return ;
        }
        recorrido = recorrido->siguiente;
    }
}
void DecidePos(string palabra,int linea, int posicion){
    if (EnPosicion(palabra)){
        InsertaNuevaPos(palabra,linea,posicion);
    } else{
        InsteraPos(linea,posicion,palabra);
    }
}
void RetornaPosiciones(string palabra){
    Posicion *recorrido = primpos;
    while (true){
        if (recorrido->palabra == palabra){
            for (int i = 0; i<recorrido->posicion.size() ; i++){
                cout << "Encontrado en linea: " << recorrido->linea[i] << " en la posicion: " << recorrido->posicion[i] << endl;
            }
            break;
        }
        recorrido = recorrido->siguiente;
    }
}
void EliminaPos(){
    if (primpos == NULL){
        return;
    } else {
        Posicion *recorrido = primpos;
        Posicion *temp;
        while (true) {
            if (recorrido->siguiente == NULL) {
                free(recorrido);
                return;
            } else {
                temp = recorrido;
                recorrido = recorrido->siguiente;
                free(temp);
            }
        }
    }
}