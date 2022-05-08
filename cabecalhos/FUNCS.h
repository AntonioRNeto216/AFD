#ifndef FUNCS_H
#define FUNCS_H

#include "./AFD.h";

/**
 * Faz a leitura do arquivo escolhido, cria a AFD e executa a busca das palavras
 * 
 * @param nomeArquivoEscolhido Arquivo escolhido
 */
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
                    } else if (index >= 3 && index <= tamMapaEstado + 2) {
                        linhaParaD.push_back(dadoChar != '_' ? dadoChar : ' ');
                    } else if (index == tamMapaEstado + 3) {
                        afd.iSetter(dadoChar);
                    } else if (index == tamMapaEstado + 4) {
                        afd.InsereNoF(dadoChar);
                    } else if (index > tamMapaEstado + 5) {
                        afd.InsereNasPalavrasTeste(dado == "_" ? "" : dado);
                    }
                }

                if (!linhaParaD.empty()) {
                    afd.InsereTransicoesEmD(linhaParaD);
                    linhaParaD.clear();
                }
                if (index == 1)
                    tamMapaEstado = afd.RetornaTamanhoEstado();
                
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

/**
 * Menu básico para escolha de arquivo
 * 
 * @return Arquivo escolhido. Ex: arquivo1.txt 
 */
string escolhaArquivo() {
    int escolha;

    do {
        cout << endl << "-----" << endl;
        cout << "Escolha uma opcao" << endl;
        cout << "[1]: arquivo1.txt" << endl;
        cout << "[2]: arquivo2.txt" << endl;
        cout << "[3]: arquivo3.txt" << endl;
        cout << "[4]: arquivo4.txt" << endl;
        cout << "[5]: arquivo5.txt" << endl;
        cout << "[0]: Sair" << endl;
        cout << "Opcao: ";
        cin >> escolha;
        cout << endl;

    } while (escolha < 0 || escolha > 5);

    if (escolha == 0) {
        cout << endl << "-----" << endl;
        cout << "Saindo !!" << endl;
        exit(0);
    }

    // Concatenação para gerar o nome do arquivo escolhido
    string arquivoEscolhido = "arquivo" + to_string(escolha) + ".txt";   

    return arquivoEscolhido;
}

#endif