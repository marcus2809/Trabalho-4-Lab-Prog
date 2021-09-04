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

        Noh* obter_dir () { /* Deve retornar ponteiro para filho direito.  */ }
        Noh* obter_esq () { /* Deve retornar ponteiro para filho esquerdo. */ }
        Noh* obter_pai () { /* Deve retornar ponteiro para o pai.          */ }

        }; // Noh  ----------------------------------------------------------------

    Noh *raiz;

    Noh* obter_raiz () { /* Deve retornar um ponteiro para a raiz,
                            ou nullptr, se a árvore estiver vazia. */ }

    private: // -----------------------------------------------------------------

    // Você pode incluir campos e métodos que importem para a implementação
    // mas que fiquem inacessíveis ao usuário da classe DicioAVL ("private").

    void transplantar (Noh *u, Noh *v) {
    
        if ( u->pai == nullptr ) { raiz = v; }

        else if ( u == (u->pai)->esq ) { (u->pai)->esq = v; }

        else { (u->pai)->dir = v; }

        if ( v != nullptr ) { v->pai = u->pai; }
    }

    public: // ------------------------------------------------------------------

    // Tudo o que está abaixo deve ser mantido público em DicioAVL,
    // pois será utilizado nos testes do professor.

    // Operações de Dicionário: -------------------------------------------------

    DicioAVL () : raiz(nullptr) { /* Deve criar um dicionário vazio. */ }

    ~DicioAVL () { /* Deve desalocar toda a memória dinamicamente alocada
                    * pelo dicionário (no caso, basicamente a árvore AVL). */ }

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

        TC chave () { /* Deve retornar a chave do elemento em questão. */ 
            return p->chave;
            }

        TV valor () { /* Deve retornar o valor do elemento em questão. */ 
            return p->valor;
            }

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

        if (raiz == nullptr) {raiz = n; Iterador i(n); return i; }

        bool inserido = false;

        Noh *temp = raiz;

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

        if (n->esq == nullptr) { transplantar(n, n->dir); }

        else if (n->dir == nullptr) { transplantar(n, n->esq); }

        else {

            Noh *s; // Noh que será o sucessor de n

            s = n->dir; while (s->esq != nullptr) s = s->esq;

            transplantar(s, s->dir);

            s->esq = n->esq;
            (n->esq)->pai = s;
            s->dir = n->dir;

            if ( n->dir != nullptr ) { (n->dir)->pai = s; }

            transplantar(n, s);

            }

        }

    }; // DicioAVL  --------------------------------------------------------------


int main ()
{
    DicioAVL<int,char> D; int i;

    for (i = 48; i < 58; ++i) if (D.inserir(i, (char) i) == D.fim()) return 1;

    for (auto it = D.inicio(); it != D.fim(); ++it) {
        cout << "O código de ’" << it.valor() << "’ é " << it.chave() << '\n';
    }
    for (i = 53; i < 58; ++i) {
        auto it = D.buscar(i);
        D.remover(it);
        cout << "Foi removido o elemento ’" << it.valor() << "’, cuja chave é " << it.chave() << '\n';
    }
    for (auto it = D.inicio(); it != D.fim(); ++it) {
        cout << "O código de ’" << it.valor() << "’ é " << it.chave() << '\n';
    }

    return 0;
}