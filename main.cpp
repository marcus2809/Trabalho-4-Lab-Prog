#include <iostream>
#include <new>

using std::cout;
using std::nothrow;

// -----------------------------------------------------------------------------
// Universidade Federal do Ceará, Centro de Ciências, Departamento de Computação
// Disciplina: Laboratório de Programação - CK0215 2021.1 T01A
// Professor: Pablo Mayckon Silva Farias
// Trabalho 4
// Interface para a Implementação de Dicionário baseado em Árvore AVL.
// Autor: Pablo Mayckon Silva Farias, em 18/08/2021.
// -----------------------------------------------------------------------------

// Tudo o que está presente na interface abaixo deve ser mantido como está,
// pois é essa interface que será utilizada no programa do professor para a
// realização dos testes.
//
// A realização do trabalho consiste portanto em *completar* a implementação
// abaixo, tornando-a funcional e atendendo aos requisitos deste trabalho.

template <typename TC, typename TV>
class DicioAVL
    {
    public: // ------------------------------------------------------------------

    // Representação Interna da Árvore ------------------------------------------

    // Numa implementação típica de dicionário,
    // a representação interna normalmente fica inacessível ao usuário;
    // neste trabalho, porém,
    // o professor precisa avaliar se a árvore está correta,
    // e por isso a estrutura do nó é exposta ao usuário ("public"):

    struct Noh
        {
        TC chave;  TV valor;

        // Você deve completar a estrutura do nó com:
        //
        // 1. Ponteiros para filho esquerdo, filho direito e pai.
        //
        // 2. Se necessário, algum campo adicional que viabilize a implementação
        //    da árvore AVL, como a altura do nó, a informação do balanceamento
        //    (-1, 0, +1), etc.
        //
        // Você é livre para escolher como vai representar os elementos acima,
        // mas deve implementar as funções abaixo,
        // que permitirão que a estrutura da árvore seja percorrida
        // (quando o filho direito / filho esquerdo / pai não existir,
        //  a respectiva função deve retornar nullptr):
        
        Noh *esq; Noh *dir; Noh *pai;
        int bal; // guarda o balanceamento do nó

        Noh* obter_dir () { /* Deve retornar ponteiro para filho direito.  */ return dir; }
        Noh* obter_esq () { /* Deve retornar ponteiro para filho esquerdo. */ return esq; }
        Noh* obter_pai () { /* Deve retornar ponteiro para o pai.          */ return pai; }

        }; // Noh  ----------------------------------------------------------------

    Noh *raiz;

    Noh* obter_raiz () { /* Deve retornar um ponteiro para a raiz,
                            ou nullptr, se a árvore estiver vazia. */ 
        return raiz;                        
    }

    private: // -----------------------------------------------------------------

    // Você pode incluir campos e métodos que importem para a implementação
    // mas que fiquem inacessíveis ao usuário da classe DicioAVL ("private").

    void transplantar (Noh *u, Noh *v) {
    
        if ( u->pai == nullptr ) { raiz = v; }

        else if ( u == (u->pai)->esq ) { (u->pai)->esq = v; }

        else { (u->pai)->dir = v; }

        if ( v != nullptr ) { v->pai = u->pai; }
    }

    void rotacaoEsq (Noh *x) {
        
        Noh *y = x->dir;
        x->dir = y->esq;

        //x->bal -= 2; y->bal -= 1;

        if (y->esq != nullptr) (y->esq)->pai = x;
        
        y->pai = x->pai;
        
        if (x->pai == nullptr) raiz = y;
        
        else if (x == (x->pai)->esq) (x->pai)->esq = y;
        
        else (x->pai)->dir = y;
        
        y->esq = x;
        x->pai = y;
    }

    void rotacaoDir (Noh *x) {
        
        Noh *y = x->esq;
        x->esq = y->dir;

        //x->bal += 2; y->bal += 1;

        if (y->dir != nullptr) (y->dir)->pai = x;
        
        y->pai = x->pai;
        
        if (x->pai == nullptr) raiz = y;
        
        else if (x == (x->pai)->dir) (x->pai)->dir = y;
        
        else (x->pai)->esq = y;
        
        y->dir = x;
        x->pai = y;
    }

    bool inserirRec (Noh *temp, Noh *n) {

        if (n->chave < temp->chave && temp->esq != nullptr) { 
            if ( inserirRec(temp->esq, n) ) {
                
                temp->bal--;

                if (temp->bal == -2) {

                    if ( (temp->esq)->bal == -1) { 
                        temp->bal = 0; (temp->esq)->bal = 0;
                        rotacaoDir(temp); return false; 
                    }

                    else if ( (temp->esq)->bal == 1) {

                        if ( ((temp->esq)->dir)->bal == 0 ) { temp->bal = 0; (temp->esq)->bal = 0; }

                        else if ( ((temp->esq)->dir)->bal == 1 ) { temp->bal = -1; (temp->esq)->bal = 0; }

                        else if ( ((temp->esq)->dir)->bal == -1 ) { temp->bal = 0; (temp->esq)->bal = 1; }

                        rotacaoEsq(temp->esq); rotacaoDir(temp); return false; }
                }
                return true; 
            }
        }

        else if (n->chave < temp->chave && temp->esq == nullptr) {
            
            n->pai = temp; temp->esq = n; temp->bal--;
            return temp->bal != 0;
        }

        else if (n->chave > temp->chave && temp->dir != nullptr) {
            if ( inserirRec(temp->dir, n) ) {
                
                temp->bal++;

                if (temp->bal == 2) {

                    if ( (temp->dir)->bal == 1) { 
                        temp->bal = 0; (temp->dir)->bal = 0;
                        rotacaoEsq(temp); return false;
                    }

                    else if ( (temp->dir)->bal == -1) {

                        if ( ((temp->dir)->esq)->bal == 0 ) { temp->bal = 0; (temp->dir)->bal = 0; }

                        else if ( ((temp->dir)->esq)->bal == 1 ) { temp->bal = 0; (temp->dir)->bal = -1; }

                        else if ( ((temp->dir)->esq)->bal == -1 ) { temp->bal = 1; (temp->dir)->bal = 0; }

                        rotacaoDir(temp->dir); rotacaoEsq(temp); return false; }
                }
                return true; 
            }
        }

        else if (n->chave > temp->chave && temp->dir == nullptr) {
            
            n->pai = temp; temp->dir = n; temp->bal++;
            return temp->bal != 0;
        }
        return false;
    }

    // Função utilizado pelo destruidor do Dicionário para desalocar a memória da árvore AVL
    void desalocar(Noh *n) {
        if (n != nullptr) {
            desalocar(n->esq);
            desalocar(n->dir);
            delete n;
        }
    }

    void consertarDir(Noh *temp) {
        
        if (temp == nullptr) return;

        Noh *pai = temp->pai;

        bool esquerda = false; // indica qual sub arvore foi alterada
        
        if ( pai != nullptr && temp == pai->esq ) esquerda = true;

        if ( temp->bal == 1 ) { temp->bal = 0; }

        else if ( temp->bal == 0 ) { temp->bal = -1; return; }

        else if ( temp->bal == -1 ) {

            if ( (temp->esq)->bal == -1) {
                    temp->bal = 0; (temp->esq)->bal = 0;
                    rotacaoDir(temp);
            }

            else if ( (temp->esq)->bal == 0) {
                temp->bal = -1; (temp->esq)->bal = 1;
                rotacaoDir(temp); return;
            }

            else if ( (temp->esq)->bal == 1) {
                
                if ( ((temp->esq)->dir)->bal == 0 ) { temp->bal = 0; (temp->esq)->bal = 0; }

                else if ( ((temp->esq)->dir)->bal == 1 ) { temp->bal = -1; (temp->esq)->bal = 0; }

                else if ( ((temp->esq)->dir)->bal == -1 ) { temp->bal = 0; (temp->esq)->bal = 1; }

                rotacaoEsq(temp->esq); rotacaoDir(temp);
            }
        }

        if (esquerda) consertarEsq(pai);
        else consertarDir(pai);
    }

    void consertarEsq(Noh *temp) {

        if (temp == nullptr) return;

        Noh *pai = temp->pai;

        bool esquerda = false; // indica qual sub arvore foi alterada
        
        if ( pai != nullptr && temp == pai->esq ) esquerda = true;

        if ( temp->bal == -1 ) { temp->bal = 0; }

        else if ( temp->bal == 0 ) { temp->bal = 1; return; }

        else if ( temp->bal == 1 ) {

            if ( (temp->dir)->bal == 1) {
                temp->bal = 0; (temp->dir)->bal = 0;
                rotacaoEsq(temp);
            }

            else if ((temp->dir)->bal == 0) {
                temp->bal = 1; (temp->dir)->bal = -1;
                rotacaoEsq(temp); return;
            }

            else if ( (temp->dir)->bal == -1) {

                if ( ((temp->dir)->esq)->bal == 0 ) { temp->bal = 0; (temp->dir)->bal = 0; }

                else if ( ((temp->dir)->esq)->bal == 1 ) { temp->bal = 0; (temp->dir)->bal = -1; }

                else if ( ((temp->dir)->esq)->bal == -1 ) { temp->bal = 1; (temp->dir)->bal = 0; }

                rotacaoDir(temp->dir); rotacaoEsq(temp);
            }
        }

        if (esquerda) consertarEsq(pai);
        else consertarDir(pai);
    }

    public: // ------------------------------------------------------------------

    // Tudo o que está abaixo deve ser mantido público em DicioAVL,
    // pois será utilizado nos testes do professor.

    // Operações de Dicionário: -------------------------------------------------

    DicioAVL () : raiz(nullptr) { /* Deve criar um dicionário vazio. */ }

    ~DicioAVL () { /* Deve desalocar toda a memória dinamicamente alocada
                    * pelo dicionário (no caso, basicamente a árvore AVL). */ 
        desalocar(raiz);
        }

    class Iterador
        {
        private: // --------------------------------------------------------------

        // Você pode incluir campos e métodos que importem para a implementação
        // mas que fiquem inacessíveis ao usuário da classe Iterador.

        // Caso você queira dar a DicioAVL acesso aos membros privados de
        // Iterador, sem que esses membros sejam acessíveis em outros contextos,
        // basta descomentar a linha abaixo:

        friend DicioAVL;

        Noh* getEsq () { return p->esq; }
        Noh* getDir () { return p->dir; }
        Noh* getPai () { return p->pai; }
        Noh* getNoh () { return p; }

        public: // ---------------------------------------------------------------

        // Tudo o que está abaixo deve ser mantido público em Iterador,
        // pois será utilizado nos testes do professor.

        // Os operadores "!=" e "==" abaixo podem ser chamados mesmo caso
        // o iterador esteja no "fim" do dicionário ("posição" em que o iterador
        // não se refere a nenhum elemento propriamente dito).

        Noh *p;

        Iterador (Noh *pnt) : p(pnt) {}

        bool operator != (Iterador j) { return p != j.p;
                                            /* Deve retornar "true" se e somente se
                                            o iterador atual e "j" NÃO SE REFEREM
                                            ao mesmo elemento ou posição do
                                            dicionário. */ }

        bool operator == (Iterador j) { return p == j.p;
                                            /* Deve retornar "true" se e somente se
                                            o iterador atual e "j" SE REFEREM
                                            ao mesmo elemento ou posição do
                                            dicionário. */ }

        // Os métodos abaixo possuem como PRÉ-CONDIÇÃO o fato de que o iterador
        // aponta para um elemento propriamente dito do dicionário
        // (será responsabilidade do usuário garantir que esse será o caso,
        //  e portanto que os métodos abaixo NÃO SERÃO CHAMADOS caso o iterador
        //  aponte para o "fim" do dicionário).
        // Portanto, esses métodos NÃO PRECISAM TESTAR se o iterador aponta
        // para o "fim" do dicionário.

        TC chave () { /* Deve retornar a chave do elemento em questão. */ return p->chave; }

        TV valor () { /* Deve retornar o valor do elemento em questão. */ return p->valor; }

        void operator ++ ()
            {
            /* Deve fazer o iterador passar ao próximo elemento do dicionário
            * (isto é, ao elemento da CHAVE SUCESSORA, na ordem crescente das
            * chaves), ou então ao "fim" do dicionário, caso não haja um
            * próximo elemento. */

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

        }; // Iterador ------------------------------------------------------------

    Iterador inicio () { /* Deve retornar um iterador para o elemento de menor
                            * chave, caso exista um, ou então um iterador para o
                            * "fim", se o dicionário estiver vazio. */ 
        Noh *n = raiz;
        
        if (n != nullptr) while (n->esq != nullptr) n = n->esq;

        Iterador i(n); return i;
        }

    Iterador fim () { /* Deve retornar um iterador num estado especial,
                        * que seja diferente do estado de um iterador que aponte
                        * para um elemento propriamente dito, e que dessa forma
                        * sirva para caracterizar a situação em que o iterador
                        * tenha atingido o "fim" do dicionário. */ 
        Iterador i(nullptr); return i;
        }

    Iterador inserir (TC c, TV v)
        {
        /* Deve inserir a chave "c" e o valor "v" no dicionário, partindo da
        * PRÉ-CONDIÇÃO de que a chave "c" não existe no dicionário -- ou seja,
        * a função não precisa nem deve fazer esse teste.
        *
        * Em caso de falha de alocação de memória, deve retornar um iterador
        * para o "fim".
        *
        * ATENÇÃO: o iterador retornado deve continuar válido e relativo ao par
        * -------  (c,v) enquanto esse par não for removido do dicionário.
        *
        * A observação acima é particularmente importante para o caso da REMOÇÃO
        * em que o nó do par a ser removido possui dois filhos. Nesse caso, não
        * basta apenas copiar os campos do nó sucessor para o nó em questão, pois
        * isso faria com que o par sucessor mudasse de nó, invalidando algum
        * iterador relativo a esse par; portanto, nesse caso da remoção, é
        * necessário que o nó do sucessor realmente ocupe o lugar da árvore que
        * estava sendo ocupado pelo nó a ser removido. */

        Noh *n = new(nothrow) Noh; if (n == nullptr) return fim();

        n->chave = c;
        n->valor = v;
        n->pai = nullptr;
        n->esq = nullptr;
        n->dir = nullptr;
        n->bal = 0;

        if (raiz == nullptr) {raiz = n; Iterador i(n); return i; }

        Noh *temp = raiz;

        inserirRec(temp, n);

        Iterador i(n); return i;
        }

    Iterador buscar (TC c)
        {
        /* Deve retornar um iterador para o elemento de chave "c", caso essa
        * chave exista no dicionário; caso a chave não esteja presente, deve
        * ser retornado um iterador para o "fim". */

        Noh *n = raiz;

        while (true) {

            if (n == nullptr || n->chave == c) { Iterador i(n); return i; }
            
            if (c < n->chave) n = n->esq;

            if (c > n->chave) n = n->dir;
            }
        }

    void remover (Iterador i)
        {
        /* Se o iterador apontar para o "fim", então a função deve simplesmente
        * retornar, deixando o dicionário inalterado. Em caso contrário, então
        * é PRÉ-CONDIÇÃO da função que o iterador estará apontando para algum
        * elemento do dicionário, o qual deverá ser removido. */

        if ( i == fim() ) { return; }

        Noh *n = i.getNoh();

        if (n->esq == nullptr) { 

            transplantar(n, n->dir);

            if (n->pai != nullptr) {
                
                if ( n->dir == (n->pai)->esq ) consertarEsq(n->pai); // altura da subarvore esquerda diminuiu
                
                else consertarDir(n->pai);
            }
        }

        else if (n->dir == nullptr) {

            transplantar(n, n->esq);

            if (n->pai != nullptr){

                if ( n->esq == (n->pai)->esq ) consertarEsq(n->pai); // altura da subarvore esquerda diminuiu
                
                else consertarDir(n->pai);
            }
        }

        else {

            Noh *s; // Noh que será o sucessor de n
            Noh *temp; // nó que receberá o nó mais profundo da árvore que foi alterado o balanceamento
            bool esquerda = false; // indica qual sub arvore foi alterada

            s = n->dir; while (s->esq != nullptr) s = s->esq;

            if (s->pai != n) { temp = s->pai; esquerda = true; }
            else temp = s;

            transplantar(s, s->dir);

            s->esq = n->esq;
            (n->esq)->pai = s;
            s->dir = n->dir;

            s->bal = n->bal;

            if ( n->dir != nullptr ) { (n->dir)->pai = s; }

            transplantar(n, s);

            if (esquerda) consertarEsq(temp);
            else consertarDir(temp);

        }
    }

    // TESTE --------------------------------------------

    // A função mostraArvore faz um desenho esquerda-direita-raiz
    // da árvore x. O desenho terá uma margem esquerda de
    // 3b espaços.
    void mostraArvore(Noh* a, int b) {
        if (a == nullptr) {
            imprimeEsp('*', b);
            return;
        }
    mostraArvore(a->dir, b+1);
    imprimeNo(a->chave, b);
    mostraArvore(a->esq, b+1);
    }

    // A função auxiliar imprimeNo imprime o caracter
    // c precedido de 3b espaços e seguido de uma mudança
    // de linha.
    void imprimeNo(int c, int b) {
        int i;
        for (i = 0; i < b; i++) printf("   ");
        printf("%d\n", c);
    }
    void imprimeEsp(char c, int b) {
        int i;
        for (i = 0; i < b; i++) printf("   ");
        printf("%c\n", c);
    }

    void EmOrdem(Noh* x) {
        
        if (x != nullptr) {
            EmOrdem(x->dir);
            cout << x->bal << '\n';
            EmOrdem(x->esq);
        }
    }

    // TESTE --------------------------------------------

}; // DicioAVL  --------------------------------------------------------------


int main ()
{
    DicioAVL<int,char> D; int i;

    for (i = 58; i >= 48; --i) if (D.inserir(i, (char) i) == D.fim()) return 1;

    D.mostraArvore(D.raiz, 5);
    D.EmOrdem(D.raiz);

    //for (auto it = D.inicio(); it != D.fim(); ++it) {
    //    cout << "O código de ’" << it.valor() << "’ é " << it.chave() << '\n';
    //}
    for (i = 47; i < 55; ++i) {
        auto it = D.buscar(i); D.remover(it);
    //    if (it != D.fim() ) 
    //        cout << "Foi removido o elemento ’" << it.valor() << "’, cuja chave é " << it.chave() << '\n';
    }
    cout << "\n------------------------------------------------\n\n";
    D.mostraArvore(D.raiz, 5);
    D.EmOrdem(D.raiz);

    //for (auto it = D.inicio(); it != D.fim(); ++it) {
    //    cout << "O código de ’" << it.valor() << "’ é " << it.chave() << '\n';
    //}

    return 0;
}