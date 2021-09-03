#include <iostream>
#include <new>

using std::cout;
using std::nothrow;

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

      Noh* obter_dir () { /* Deve retornar ponteiro para filho direito.  */ }
      Noh* obter_esq () { /* Deve retornar ponteiro para filho esquerdo. */ }
      Noh* obter_pai () { /* Deve retornar ponteiro para o pai.          */ }

     }; // Noh  ----------------------------------------------------------------

   Noh* obter_raiz () { /* Deve retornar um ponteiro para a raiz,
                           ou nullptr, se a árvore estiver vazia. */ }

   private: // -----------------------------------------------------------------

   // Você pode incluir campos e métodos que importem para a implementação
   // mas que fiquem inacessíveis ao usuário da classe DicioAVL ("private").

   public: // ------------------------------------------------------------------

   // Tudo o que está abaixo deve ser mantido público em DicioAVL,
   // pois será utilizado nos testes do professor.

   // Operações de Dicionário: -------------------------------------------------

   DicioAVL () { /* Deve criar um dicionário vazio. */ }

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
      // friend DicioAVL;

      public: // ---------------------------------------------------------------

      // Tudo o que está abaixo deve ser mantido público em Iterador,
      // pois será utilizado nos testes do professor.

      // Os operadores "!=" e "==" abaixo podem ser chamados mesmo caso
      // o iterador esteja no "fim" do dicionário ("posição" em que o iterador
      // não se refere a nenhum elemento propriamente dito).

      bool operator != (Iterador j) { /* Deve retornar "true" se e somente se
                                         o iterador atual e "j" NÃO SE REFEREM
                                         ao mesmo elemento ou posição do
                                         dicionário. */ }

      bool operator == (Iterador j) { /* Deve retornar "true" se e somente se
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

      TC chave () { /* Deve retornar a chave do elemento em questão. */ }

      TV valor () { /* Deve retornar o valor do elemento em questão. */ }

      void operator ++ ()
        {
         /* Deve fazer o iterador passar ao próximo elemento do dicionário
          * (isto é, ao elemento da CHAVE SUCESSORA, na ordem crescente das
          * chaves), ou então ao "fim" do dicionário, caso não haja um
          * próximo elemento. */
        }

     }; // Iterador ------------------------------------------------------------

   Iterador inicio () { /* Deve retornar um iterador para o elemento de menor
                         * chave, caso exista um, ou então um iterador para o
                         * "fim", se o dicionário estiver vazio. */ }

   Iterador fim () { /* Deve retornar um iterador num estado especial,
                      * que seja diferente do estado de um iterador que aponte
                      * para um elemento propriamente dito, e que dessa forma
                      * sirva para caracterizar a situação em que o iterador
                      * tenha atingido o "fim" do dicionário. */ }

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
     }

   Iterador buscar (TC c)
     {
      /* Deve retornar um iterador para o elemento de chave "c", caso essa
       * chave exista no dicionário; caso a chave não esteja presente, deve
       * ser retornado um iterador para o "fim". */
     }

   void remover (Iterador i)
     {
      /* Se o iterador apontar para o "fim", então a função deve simplesmente
       * retornar, deixando o dicionário inalterado. Em caso contrário, então
       * é PRÉ-CONDIÇÃO da função que o iterador estará apontando para algum
       * elemento do dicionário, o qual deverá ser removido. */
     }

  }; // DicioAVL  --------------------------------------------------------------

// Dicionário baseado em Árvore AVL
template <typename TC, typename TV> 
class MeuDicioAVL{

    public:

    struct Noh {
        TC chave; TV valor; 
        Noh *esq; Noh *dir; Noh *pai;

        Noh* obter_dir () { /* Deve retornar ponteiro para filho direito.  */ }
        Noh* obter_esq () { /* Deve retornar ponteiro para filho esquerdo. */ }
        Noh* obter_pai () { /* Deve retornar ponteiro para o pai.          */ }
    };

    Noh *raiz;

    Noh* obter_raiz () { /* Deve retornar um ponteiro para a raiz,
                           ou nullptr, se a árvore estiver vazia. */ }

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

    ~DicioAVL () { /* Deve desalocar toda a memória dinamicamente alocada
                   * pelo dicionário (no caso, basicamente a árvore AVL). */ }

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