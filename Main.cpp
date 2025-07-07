// main.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib> // Para system() e srand(), rand()
#include <ctime>   // Para time()
#include "Loja.h"        // Inclui a definição da classe Loja
#include "utilitario.h"  // Inclui as declarações de todas as funções utilitárias e de menu

using namespace std;

// --- NENHUMA FUNÇÃO DE MENU DEVE SER DEFINIDA AQUI ---
// Apenas a função main() deve estar presente.

// Função principal
int main() {
    // Configura a localização para UTF-8 no Windows para exibir caracteres especiais corretamente
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    // Inicializa o gerador de números aleatórios (usado para IDs ou outras finalidades, se aplicável)
    srand(static_cast<unsigned int>(time(nullptr)));

    Loja loja; // Cria uma instância da classe Loja

    // Inicializa os dados da loja. Esta chamada foi movida do construtor da Loja para aqui
    // para evitar que os prompts de "Pressione qualquer tecla para continuar..." apareçam
    // antes do menu principal.
    loja.inicializarDadosIniciais();

    int opcao;
    do {
        limparTela(); // Limpa a tela do console
        cout << "=============== SISTEMA DE GESTÃO DE LOJA ===============\n";
        cout << "1. Efetuar Venda\n";
        cout << "2. Gestão de Clientes\n";
        cout << "3. Gestão de Produtos\n";
        cout << "4. Relatórios\n";
        cout << "0. Sair\n";
        cout << "========================================================\n";

        opcao = obterInt("Escolha uma opção: "); // Obtém a opção do usuário usando a função utilitária

        switch (opcao) {
        case 1:
            menuVendas(loja); // Chama o menu de vendas
            break;
        case 2:
            menuClientes(loja); // Chama o menu de gestão de clientes
            break;
        case 3:
            menuProdutos(loja); // Chama o menu de gestão de produtos
            break;
        case 4:
            menuRelatorios(loja); // Chama o menu de relatórios
            break;
        case 0:
            cout << "Obrigado por usar o sistema!\n";
            pausar(); // Pausa para o usuário ver a mensagem de saída
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
            pausar(); // Pausa para o usuário ver a mensagem de erro
            break;
        }
    } while (opcao != 0); // Continua o loop do menu principal até o usuário escolher sair (opção 0)

    return 0; // Indica que o programa terminou com sucesso
}