#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

/**
 * Autômato Finito Determinístico
 */
class AFD {
private:

    // Map que guarda as posições dos estados em D
    map<string, int> mapaEstados;

    // Map que guarda as posições dos símbolos em D
    map<string, int> mapaSimbolos;

    // Matriz que representa as funções de transição -> Estado x Símbolo
    vector<vector<string>> D;

    // Atributo para armazenar o estado inicial
    string i; // ! talvez armazenar em int

    // Vetor para armazenar os estados finais
    vector<string> F;

    // Todas as palavras que serão verificadas
    vector<string> palavrasTeste;

    // void VerificaPalavra(string &palavra);

public:

    AFD() {
        cout << "CRIOU" << endl;
    }

    // ~AFD() {

    // }

    void InsereEstado(string estado);
    void InsereSimbolos(string simbolo);
    int RetornaTamanhoEstado();
    void InsereTransicoesEmD(vector<string> novaLinha);
    void iSetter(string iValor);
    void InsereNoF(string novoEstadoFinal);
    void InsereNasPalavrasTeste(string novaPalavraTeste);
    void PrintInformacoes();
};

/**
 * Adiciona o estado no mapaEstados
 * @param estado Estado que estamos adicionando
 */
void AFD::InsereEstado(string estado) {
    int valorChave = mapaEstados.size();
    mapaEstados[estado] = valorChave;
}

/**
 * Adiciona o símbolo no mapaSimbolos
 * @param simbolo Símbolo que estamos adicionando
 */
void AFD::InsereSimbolos(string simbolo) {
    int valorChave = mapaSimbolos.size();
    mapaSimbolos[simbolo] = valorChave;
}

/**
 * Retorna a quantidade de estados
 * @return O tamanho do mapaEstado
 */
int AFD::RetornaTamanhoEstado() {
    return mapaEstados.size();
}

/**
 * Insere uma nova linha na matriz D
 * @param novaLinha Vector contendo as transições do estado
 */
void AFD::InsereTransicoesEmD(vector<string> novaLinha) {
    D.push_back(novaLinha);
}

/**
 * Setter do atributo privado i
 * @param iValor Novo valor para i
 */
void AFD::iSetter(string iValor) {
    i = iValor;
}

/**
 * Inserindo novo estado final em F
 * @param novoEstadoFinal Novo estado final para o vector
 */
void AFD::InsereNoF(string novoEstadoFinal) {
    F.push_back(novoEstadoFinal);
}

/**
 * Inserindo nova palavra para teste em palavrasTeste
 * @param novaPalavraTeste Nova palavra para testar
 */
void AFD::InsereNasPalavrasTeste(string novaPalavraTeste) {
    palavrasTeste.push_back(novaPalavraTeste);
}

/**
 * Print de todos os atributos do AFD. Método para verificação
 */
void AFD::PrintInformacoes() {
    cout << "-- Mapa Estados" << endl;
    for (auto p : mapaEstados)
        cout << "Chave: " << p.first << " | Valor: " << p.second << endl;

    cout << "-- Mapa Simbolos" << endl;
    for (auto p : mapaSimbolos)
        cout << "Chave: " << p.first << " | Valor: " << p.second << endl;

    cout << "-- Matriz D" << endl;
    for(auto linhaEstado : D){
        for(auto simbolo : linhaEstado)
            cout << simbolo << " ";
        cout << endl;
    }

    cout << "-- Valor de i: " << i << endl;

    cout << "-- Vetor de estados finais" << endl;
    for (auto estadoFinal : F)
        cout << estadoFinal << endl;

    cout << "-- Vetor de palavras teste" << endl;
    for (auto palavraTeste : palavrasTeste)
        cout << palavraTeste << endl;
}

void gerandoAFD(string &nomeArquivoEscolhido) {

    // Escolhendo arquivo que vai ser aberto
    ifstream arquivo ("./arquivosDeEntrada/" + nomeArquivoEscolhido);

    // Instância do objeto AFD
    AFD afd;

    if (arquivo.is_open()) {
        
        // Usado para manipular as linhas obtidas do arquivo
        istringstream iss;

        // Variável que será usada para receber as linhas do arquivo
        string linha;

        // Variável que será usada para receber os dados das linhas de forma separada
        string dado;

        // Indica em qual linha estamos. Logo, qual informação teremos que armazenar
        int index = 1;

        // Necessário para evitar chamar o método RetornaTamanhoEstado todo momento
        int tamMapaEstado = 0;

        // Necessário para ajustar os valores na matriz D (atributo da AFD)
        vector<string> linhaParaD;

        while (!arquivo.eof()) {
            getline(arquivo, linha);

            if (!linha.empty()) {
                
                iss.clear();
                iss.str(linha);

                while (iss.good()) {
                    iss >> dado;

                    if (index == 1) {
                        afd.InsereEstado(dado);
                    } else if (index == 2) {
                        afd.InsereSimbolos(dado);
                        tamMapaEstado = afd.RetornaTamanhoEstado();
                    } else if (index >= 3 && index <= tamMapaEstado + 2) {
                        linhaParaD.push_back(dado != "_" ? dado : " ");
                    } else if (index == tamMapaEstado + 3) {
                        afd.iSetter(dado);
                    } else if (index == tamMapaEstado + 4) {
                        afd.InsereNoF(dado);
                    } else if (index > tamMapaEstado + 5) {
                        afd.InsereNasPalavrasTeste(dado);
                    }
                }

                if (!linhaParaD.empty()) {
                    afd.InsereTransicoesEmD(linhaParaD);
                    linhaParaD.clear();
                }
                index++;
            }
        }
        arquivo.close();
    } else {
        cout << "Problema ao abrir o arquivo !!" << endl;
        return;
    }

    afd.PrintInformacoes();
    // ! Executar AFD
}

int main() {
    string arquivo = "arquivo1.txt";

    gerandoAFD(arquivo);

    return 0;
}