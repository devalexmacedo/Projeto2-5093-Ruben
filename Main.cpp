// main.cpp - Programa principal
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <utility> // para std::pair
#include "Loja.h"
#include <locale>

using namespace std;

// Função para limpar a tela (funciona em Windows e sistemas Unix-like)
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função auxiliar para limpar o buffer de entrada e tratar erros
void limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Função para tratar entrada inválida
void tratarErroEntrada() {
    cout << "Entrada inválida. Por favor, tente novamente.\n";
    cin.clear(); // Limpa os flags de erro
    limparBufferEntrada(); // Descarta a entrada inválida
}

// Função para obter um inteiro válido do usuário
int validacaoInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n) {
            limparBufferEntrada();
            return n;
        }
        else {
            tratarErroEntrada();
        }
    }
    return n;
}

// Função para obter um float válido do usuário
float obterFloat(const string& prompt) {
    float valor;
    while (true) {
        cout << prompt;
        if (cin >> valor && valor > 0) {
            limparBufferEntrada();
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

// Função para exibir o menu principal
void exibirMenuPrincipal() {
    // Definir as opções do menu
    vector<pair<int, string>> menuOpcoes = {
        {1, "Efetuar Venda"},
        {2, "Gestão de estoque"},
        {3, "Gestão de clientes"},
        {4, "Relatórios"},
        {0, "Sair"}
    };

    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    cout << "------------------ MENU PRINCIPAL -----------------" << endl;
    cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
    cout << linhaSeparadora << endl;

    for (const auto& item : menuOpcoes) {
        cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
    }

    cout << linhaSeparadora << endl;
}

// Função para exibir o menu de gestão de estoque
void exibirMenuEstoque() {
    // Definir as opções do menu
    vector<pair<int, string>> menuOpcoes = {
        {1, "Adicionar novo produto"},
        {2, "Adicionar estoque a produto existente"},
        {3, "Eliminar produto"},
        {4, "Listar produtos"},
        {0, "Voltar"}
    };

    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    cout << "--------------- GESTÃO DE ESTOQUE ----------------" << endl;
    cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
    cout << linhaSeparadora << endl;

    for (const auto& item : menuOpcoes) {
        cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
    }

    cout << linhaSeparadora << endl;
}

// Função para exibir o menu de gestão de clientes
void exibirMenuClientes() {
    // Definir as opções do menu
    vector<pair<int, string>> menuOpcoes = {
        {1, "Adicionar novo cliente"},
        {2, "Eliminar cliente"},
        {3, "Alterar nome do cliente"},
        {4, "Listar clientes"},
        {0, "Voltar"}
    };

    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    cout << "--------------- GESTÃO DE CLIENTES ---------------" << endl;
    cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
    cout << linhaSeparadora << endl;

    for (const auto& item : menuOpcoes) {
        cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
    }

    cout << linhaSeparadora << endl;
}

// Função para exibir o menu de relatórios
void exibirMenuRelatorios() {
    // Definir as opções do menu
    vector<pair<int, string>> menuOpcoes = {
        {1, "Relatório de estoque"},
        {2, "Relatório de vendas por produto"},
        {3, "Relatório total de vendas"},
        {0, "Voltar"}
    };

    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    cout << "------------------- RELATÓRIOS -------------------" << endl;
    cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
    cout << linhaSeparadora << endl;

    for (const auto& item : menuOpcoes) {
        cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
    }

    cout << linhaSeparadora << endl;
}

int main() {
    setlocale(LC_ALL, "pt_PT.UTF-8");
    // Criar uma instância da loja
    Loja loja;

    int opcao = -1;

    // Loop principal do programa
    while (opcao != 0) {
        limparTela();
        exibirMenuPrincipal();
        opcao = validacaoInt("Escolha uma opção: ");

        switch (opcao) {
        case 1: {
            // Efetuar venda
            limparTela();
            cout << "===== EFETUAR VENDA =====\n";

            // Listar clientes
            loja.listarClientes();

            // Selecionar cliente
            int idCliente;
            idCliente = validacaoInt("Digite o ID do cliente: ");

            // Iniciar venda
            loja.iniciarVenda(idCliente);

            // Adicionar itens à venda
            char continuar = 'S';
            while (continuar == 'S' || continuar == 's') {
                // Listar produtos
                loja.listarProdutos();

                // Selecionar produto por ID
                int idProduto;
                int quantidade;

                cout << "Digite o ID do produto: ";
                cin >> idProduto;

                Produto* produto = loja.buscarProdutoPorId(idProduto);
                if (produto == nullptr) {
                    cout << "Produto não encontrado!\n";
                    continue; // volta ao início do loop
                }

                quantidade = validacaoInt("Digite a quantidade: ");

                // Adicionar item à venda
                loja.adicionarItemVenda(idProduto, quantidade);

                cout << "Adicionar mais itens? (S/N): ";
                cin >> continuar;
                cin.ignore();
            }

            // Checkout da venda
            if (loja.checkoutVenda()) {
                // Finalizar venda
                double valorEntregue;
                valorEntregue = obterFloat("Digite o valor entregue pelo cliente: ");

                while (valorEntregue <= 0) {
                    valorEntregue = obterFloat("Valor inválido. Digite o valor entregue pelo cliente: ");
                }

                loja.finalizarVenda(valorEntregue);
            }

            cout << "Pressione Enter para continuar...";
            cin.get();
            break;
        }

        case 2: {
            // Gestão de estoque
            int opcaoEstoque = -1;

            while (opcaoEstoque != 0) {
                limparTela();
                exibirMenuEstoque();
                opcaoEstoque = validacaoInt("Escolha uma opção: ");

                switch (opcaoEstoque) {
                case 1: {
                    // Adicionar novo produto
                    char nome[50];
                    int quantidade;
                    double precoCusto;

                    cout << "Nome do produto: ";
                    cin.ignore();
                    cin.getline(nome, 50);

                    quantidade = validacaoInt("Quantidade inicial: ");

                    precoCusto = obterFloat("Preço de custo: ");

                    loja.adicionarProduto(nome, quantidade, precoCusto);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 2: {
                    // Adicionar estoque a produto existente
                    loja.listarProdutos();

                    int idProduto;
                    int quantidade;

                    idProduto = validacaoInt("ID do produto: ");

                    quantidade = validacaoInt("Quantidade a adicionar: ");

                    loja.atualizarEstoque(idProduto, quantidade);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 3: {
                    // Eliminar produto
                    loja.listarProdutos();

                    int idProduto;
                    idProduto = validacaoInt("ID do produto a eliminar: ");

                    loja.eliminarProduto(idProduto);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 4: {
                    // Listar produtos
                    loja.listarProdutos();

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }
                }
            }
            break;
        }

        case 3: {
            // Gestão de clientes
            int opcaoClientes = -1;

            while (opcaoClientes != 0) {
                limparTela();
                exibirMenuClientes();
                opcaoClientes = validacaoInt("Escolha uma opção: ");

                switch (opcaoClientes) {
                case 1: {
                    // Adicionar novo cliente
                    char nome[50];
                    char telefone[20];
                    char morada[100];

                    cout << "Nome do cliente: ";
                    cin.ignore();
                    cin.getline(nome, 50);

                    cout << "Telefone: ";
                    cin.getline(telefone, 20);

                    cout << "Morada: ";
                    cin.getline(morada, 100);

                    loja.adicionarCliente(nome, telefone, morada);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 2: {
                    // Eliminar cliente
                    loja.listarClientes();

                    int idCliente;
                    idCliente = validacaoInt("ID do cliente a eliminar: ");

                    loja.eliminarCliente(idCliente);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 3: {
                    // Alterar nome do cliente
                    loja.listarClientes();

                    int idCliente;
                    char novoNome[50];

                    idCliente = validacaoInt("ID do cliente: ");

                    cout << "Novo nome: ";
                    cin.ignore();
                    cin.getline(novoNome, 50);

                    loja.alterarNomeCliente(idCliente, novoNome);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 4: {
                    // Listar clientes
                    loja.listarClientes();

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }
                }
            }
            break;
        }

        case 4: {
            // Relatórios
            int opcaoRelatorios = -1;

            while (opcaoRelatorios != 0) {
                limparTela();
                exibirMenuRelatorios();
                opcaoRelatorios = validacaoInt("Escolha uma opção: ");

                switch (opcaoRelatorios) {
                case 1: {
                    // Relatório de estoque
                    loja.relatorioEstoque();

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 2: {
                    // Relatório de vendas por produto
                    char nomeProduto[50];

                    cout << "Nome do produto: ";
                    cin.ignore();
                    cin.getline(nomeProduto, 50);

                    loja.relatorioVendasPorProduto(nomeProduto);

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }

                case 3: {
                    // Relatório total de vendas
                    loja.relatorioTotalVendas();

                    cout << "Pressione Enter para continuar...";
                    cin.get();
                    break;
                }
                }
            }
            break;
        }
        }
    }

    cout << "Obrigado por utilizar o Sistema de Gestão de Comércio!\n";

    return 0;
}

