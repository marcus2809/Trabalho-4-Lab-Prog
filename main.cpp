#include <iostream>
#include <new>

using std::cout;
using std::nothrow;

template <typename TC, typename TV> 
class DicioAVL{

    private:

    struct Noh {TC chave; TV valor; Noh *esq; Noh *dir; Noh *pai };

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
    }

    DicioAVL () : raiz(nullptr) {}

    Iterator inicio() {

        Noh *p = raiz;
        
        if  (p != nullptr) while (p->esq != nullptr) p = p->esq;

        Iterator i(p); return i;
    }

    Iterator fim() { Iterator i(nullptr); return i; }

    Iterator inserir(TC c, TV v) { 

        Noh *n = new(nothrow) Noh; if (n == nullptr) return fim();

        /*Implementação*/

        Iterator i(n); return i;
    }

    Iterator buscar (TC c) { /*Implemetação*/ }

    void remover (Iterator i) { /*Implemetação*/ }

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
}