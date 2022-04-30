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
    map<char, int> mapaEstados;

    // Map que guarda as posições dos símbolos em D
    map<char, int> mapaSimbolos;

    // Matriz que representa as funções de transição -> Estado x Símbolo
    vector<vector<char>> D;

    // Atributo para armazenar o estado inicial
    char i;

    // Vetor para armazenar os estados finais
    vector<char> F;

    // Todas as palavras que serão verificadas
    vector<string> palavrasTeste;

    void VerificaPalavra(string &palavra);
    bool eEstadoFinal(char estado);

public:

    AFD() {
        cout << "CRIOU" << endl;
    }

    // ~AFD() {

    // }

    void InsereEstado(char estado);
    void InsereSimbolos(char simbolo);
    int RetornaTamanhoEstado();
    void InsereTransicoesEmD(vector<char> novaLinha);
    void iSetter(char iValor);
    void InsereNoF(char novoEstadoFinal);
    void InsereNasPalavrasTeste(string novaPalavraTeste);
    void PrintInformacoes();
    void Executa();
};

/**
 * Adiciona o estado no mapaEstados
 * @param estado Estado que estamos adicionando
 */
void AFD::InsereEstado(char estado) {
    int valorChave = mapaEstados.size();
    mapaEstados[estado] = valorChave;
}

/**
 * Adiciona o símbolo no mapaSimbolos
 * @param simbolo Símbolo que estamos adicionando
 */
void AFD::InsereSimbolos(char simbolo) {
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
void AFD::InsereTransicoesEmD(vector<char> novaLinha) {
    D.push_back(novaLinha);
}

/**
 * Setter do atributo privado i
 * @param iValor Novo valor para i
 */
void AFD::iSetter(char iValor) {
    i = iValor;
}

/**
 * Inserindo novo estado final em F
 * @param novoEstadoFinal Novo estado final para o vector
 */
void AFD::InsereNoF(char novoEstadoFinal) {
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

/**
 * Método que gerencia todo o processo de verificação
 */
void AFD::Executa() {
    for (auto palavraTeste : palavrasTeste) {
        VerificaPalavra(palavraTeste);
    }
}

/**
 * Executa toda a lógica de verificação da palavra enviada
 * @param palavra Palavra que deve ser validada no autômato
 */
void AFD::VerificaPalavra(string &palavra) {
    char estadoAtual = i;
    for (int index = 0; index < palavra.size(); index++) {

        cout << "-> " << estadoAtual << " ";

        char letra = palavra[index];
        estadoAtual = D[mapaEstados[estadoAtual]][mapaSimbolos[letra]];
        if (estadoAtual == ' ') {
            cout << endl << "-----" << endl;
            cout << "Chegamos em um estado que não possuia mais os caminhos que sua palavra precisa" << endl;
            cout << "-----" << endl << endl;
            return;
        } else if (index == palavra.size() - 1) {
            cout << "-> " << estadoAtual << " ";

            string fraseFinal = eEstadoFinal(estadoAtual) ? "| foi aceita pelo AFD !!" : "| nao foi aceita !!";
            cout << endl << "-----" << endl;
            cout << "A palavra: |" << palavra << fraseFinal << endl;
            cout << "-----" << endl << endl;
        }
    }
}

/**
 * Verifica se o estado é final
 * @param estado Estado que será verificado
 */
bool AFD::eEstadoFinal(char estado) {
    bool resposta;
    for (auto e : F)
        resposta = e == estado;

    return resposta;
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
        vector<char> linhaParaD;

        while (!arquivo.eof()) {
            getline(arquivo, linha);

            if (!linha.empty()) {
                
                iss.clear();
                iss.str(linha);

                while (iss.good()) {
                    iss >> dado;

                    // Variável que será usada para quase todos os casos abaixo
                    char dadoChar = dado.at(0);

                    if (index == 1) {
                        afd.InsereEstado(dadoChar);
                    } else if (index == 2) {
                        afd.InsereSimbolos(dadoChar);
                        tamMapaEstado = afd.RetornaTamanhoEstado();
                    } else if (index >= 3 && index <= tamMapaEstado + 2) {
                        linhaParaD.push_back(dadoChar != '_' ? dadoChar : ' ');
                    } else if (index == tamMapaEstado + 3) {
                        afd.iSetter(dadoChar);
                    } else if (index == tamMapaEstado + 4) {
                        afd.InsereNoF(dadoChar);
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

    // Método caso seja necessário visualizar os dados do AFD
    // afd.PrintInformacoes();
    afd.Executa();
}

int main() {
    string arquivo = "arquivo1.txt";

    gerandoAFD(arquivo);

    return 0;
}