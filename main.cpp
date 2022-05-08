#include "cabecalhos/FUNCS.h";


int main() {

    // Busca o arquivo desejado
    string arquivo = escolhaArquivo();

    // Gera AFD com base no arquivo escolhido
    gerandoAFD(arquivo);

    return 0;
}