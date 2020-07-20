#include <set>
using namespace std;
typedef struct _Nodelim{
    set<char> tree;
}Nodelim;
Nodelim PalabrasNoDelimitadoras;
bool BuscaNodelim(char word){
    set<char>::iterator it;
    for (it=PalabrasNoDelimitadoras.tree.begin(); it != PalabrasNoDelimitadoras.tree.end(); it++){
        if (*it == word){
            return true;
        }
    }
    return false;
}
void InsertaNodelim(char word){
    PalabrasNoDelimitadoras.tree.insert(word);
}
void RemueveNodelim(char word){
    PalabrasNoDelimitadoras.tree.erase(word);
}
