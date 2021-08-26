#include <iostream>
#include <new>

using std::cout;
using std::nothrow;

// Dicionário baseado em Árvore AVL
template <typename TC, typename TV> 
class DicioAVL{

    private:

    struct Noh {TC chave; TV valor; Noh *esq; Noh *dir; Noh *pai; };

    Noh *raiz;

    public:

    class Iterator {

        private:

        Noh *p;

        public:

        Iterator (Noh *pnt) : p(pnt) {}

        bool operator == (Iterator j) { return p == j.p; }

        bool operator != (Iterator j) { return p != j.p; }

        void operator ++ () {

            if (p != nullptr && p->dir != nullptr) {

                p = p->dir; while (p->esq != nullptr) p = p->esq; return;
            }

            else if (p != nullptr) {

                TC temp = p->chave;

                while (p->pai != nullptr ) {

                    p = p->pai; if (p->chave > temp) return;
                }
            }

            p = nullptr;
        }

        TV valor () { return p->valor; }

        TC chave () { return p->chave; }
    };

    // Construtor do dicionário baseado em Árvore AVL
    DicioAVL () : raiz(nullptr) {}

    // Iterador que aponta o início do dicionário
    Iterator inicio() {

        Noh *n = raiz;
        
        if  (n != nullptr) while (n->esq != nullptr) n = n->esq;

        Iterator i(n); return i;
    }

    // Iterador que aponta o fim do dicionário
    Iterator fim() { Iterator i(nullptr); return i; }

    // Insire um elemento no dicionário
    Iterator inserir(TC c, TV v) { 

        Noh *n = new(nothrow) Noh; if (n == nullptr) return fim();

        n->chave = c;
        n->valor = v;
        n->pai = nullptr;
        n->esq = nullptr;
        n->dir = nullptr;

        bool inserido = false;

        Noh *temp = raiz;

        if (raiz == nullptr) {raiz = n; Iterator i(n); return i; }

        while (!inserido) {

            if (c < temp->chave && temp->esq != nullptr) { temp = temp->esq; }

            else if (c < temp->chave && temp->esq == nullptr) {
                
                n->pai = temp; temp->esq = n; inserido = true;
            }

            else if (c > temp->chave && temp->dir != nullptr) { temp = temp->dir; }

            else if (c > temp->chave && temp->dir == nullptr) {
                
                n->pai = temp; temp->dir = n; inserido = true;
            }
        }

        Iterator i(n); return i;
    }

    // Busca um elemento no dicionário
    Iterator buscar (TC c) {

        Noh *n = raiz;

        while (true) {

            if (n == nullptr || n->chave == c) { Iterator i(n); return i; }
            
            if (c < n->chave) n = n->esq;

            if (c > n->chave) n = n->dir;
        }
    }

    // Remove um elemento do dicionário
    void remover (Iterator i) { /*Implemetação*/ }

    // Indica se o dicionário está vazio
    bool vazio () { return (raiz == nullptr); }
    
};

int main ()
{
    DicioAVL<int,char> D; int i;

    for (i = 48; i < 58; ++i) if (D.inserir(i, (char) i) == D.fim()) return 1;

    for (auto it = D.inicio(); it != D.fim(); ++it) {
        cout << "O código de ’" << it.valor() << "’ é " << it.chave() << '\n';
    }
    for (i = 48; i < 58; ++i) {
        auto it = D.buscar(i);
    }

    return 0;
}