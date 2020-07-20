#include <iostream>
#include <unordered_map>
#include <sstream>
#include "Posicion.cpp"
using namespace std;
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
void DevuelveHashPos(){
    for (pair<string, int> encontro : raiz.TablaHash) {
        cout << encontro.first << " con " << encontro.second << " ocurrencias" << endl;
        RetornaPosiciones(encontro.first);
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
        cout << encontro->first + " con " + to_string(encontro->second) + " ocurrencias" + '\n';
        RetornaPosiciones(palabra);
        return "";
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
void EliminaHash(){
    raiz.TablaHash.clear();
}