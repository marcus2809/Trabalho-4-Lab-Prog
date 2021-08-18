#include <iostream>
using std::cout;

template <typename T1, typename T2> 
class DicioAVL{};

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