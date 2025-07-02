#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Loja.h"
#include <algorithm>

#ifdef _WIN32
    #include <conio.h>
    #define GETCH() _getch()
#else
    #include <termios.h>
    #include <unistd.h>
    // Implementação de getch para sistemas Unix-like
    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
    #define GETCH() getch()
#endif

using namespace std;

// Limpa o buffer de entrada para evitar problemas
void limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Trata erros de entrada inválida
void tratarErroEntrada() {
    cout << "Entrada inválida. Por favor, tente novamente.\n";
    cin.clear();
    limparBufferEntrada();
}

// Obtém um número inteiro válido do usuário
int obterInt(const string& prompt) {
    int n;
    string entrada;

    while (true) {
        cout << prompt;
        getline(cin, entrada);

        // Verifica se a entrada não está vazia
        if (entrada.empty()) {
            cout << "Entrada inválida. Por favor, digite um número.\n";
            continue;
        }

        stringstream ss(entrada);
        if (ss >> n && ss.eof() && n >= 0) {
            return n;
        }
        else {
            cout << "Entrada inválida. Por favor, digite apenas números inteiros positivos.\n";
        }
    }
}

// Obtém um número inteiro positivo (maior que 0) do usuário
int obterIntPositivo(const string& prompt) {
    int n;
    string entrada;

    while (true) {
        cout << prompt;
        getline(cin, entrada);

        // Verifica se a entrada não está vazia
        if (entrada.empty()) {
            cout << "Entrada inválida. Por favor, digite um número.\n";
            continue;
        }

        stringstream ss(entrada);
        if (ss >> n && ss.eof() && n > 0) {
            return n;
        }
        else {
            cout << "Entrada inválida. Por favor, digite apenas números inteiros maiores que 0.\n";
        }
    }
}

// Obtém um número float válido do usuário
float obterFloat(const string& prompt) {
    string entrada;
    float valor;

    while (true) {
        cout << prompt;
        getline(cin, entrada);

        // Verifica se a entrada não está vazia
        if (entrada.empty()) {
            cout << "Entrada inválida. Por favor, digite um valor.\n";
            continue;
        }

        // Substitui vírgulas por pontos para aceitar ambos os formatos
        replace(entrada.begin(), entrada.end(), ',', '.');

        stringstream ss(entrada);
        if (ss >> valor && ss.eof() && valor >= 0) {
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

// Obtém uma string do usuário
string obterString(const string& prompt) {
    string valor;
    cout << prompt;
    getline(cin, valor);
    return valor;
}

// Pausa a execução até o usuário pressionar uma tecla
void pausar() {
    cout << "\nPressione qualquer tecla para continuar...";
    (void)GETCH(); // Cast para void para ignorar o valor de retorno
}

// Limpa a tela do console
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Menu de gestão de clientes
void menuClientes(Loja& loja) {
    int opcao;
    do {
        limparTela();
        cout << "=============== GESTÃO DE CLIENTES ===============\n";
        cout << "1. Listar Clientes\n";
        cout << "2. Adicionar Cliente\n";
        cout << "3. Alterar Nome do Cliente\n";
        cout << "4. Remover Cliente\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "==================================================\n";

        opcao = obterInt("Escolha uma opção: ");

        switch (opcao) {
            case 1: {
                limparTela();
                loja.listarClientes();
                pausar();
                break;
            }
            case 2: {
                limparTela();
                string nome = obterString("Nome do cliente: ");
                string telefone = obterString("Telefone: ");
                string morada = obterString("Morada: ");

                int id = loja.adicionarCliente(nome, telefone, morada);
                cout << "Cliente adicionado com ID: " << id << endl;
                pausar();
                break;
            }
            case 3: {
                limparTela();
                loja.listarClientes();
                int id = obterInt("ID do cliente a alterar: ");
                string novoNome = obterString("Novo nome: ");

                if (loja.alterarNomeCliente(id, novoNome)) {
                    cout << "Nome alterado com sucesso!\n";
                } else {
                    cout << "Cliente não encontrado!\n";
                }
                pausar();
                break;
            }
            case 4: {
                limparTela();
                loja.listarClientes();
                int id = obterInt("ID do cliente a remover: ");

                if (loja.removerCliente(id)) {
                    cout << "Cliente removido com sucesso!\n";
                } else {
                    cout << "Cliente não encontrado!\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

// Menu de gestão de produtos
void menuProdutos(Loja& loja) {
    int opcao;
    do {
        limparTela();
        cout << "=============== GESTÃO DE PRODUTOS ===============\n";
        cout << "1. Listar Produtos\n";
        cout << "2. Adicionar Produto\n";
        cout << "3. Adicionar Stock\n";
        cout << "4. Atualizar Preço\n";
        cout << "5. Remover Produto\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "==================================================\n";

        opcao = obterInt("Escolha uma opção: ");

        switch (opcao) {
            case 1: {
                limparTela();
                loja.listarProdutos();
                pausar();
                break;
            }
            case 2: {
                limparTela();
                string nome = obterString("Nome do produto: ");
                int quantidade = obterIntPositivo("Quantidade inicial: ");
                float precoCusto = obterFloat("Preço de custo: ");

                int id = loja.adicionarProduto(nome, quantidade, precoCusto);
                cout << "Produto adicionado com ID: " << id << endl;
                pausar();
                break;
            }
            case 3: {
                limparTela();
                loja.listarProdutos();
                int id = obterIntPositivo("ID do produto: ");
                int quantidade = obterIntPositivo("Quantidade a adicionar: ");

                if (loja.adicionarEstoque(id, quantidade)) {
                    cout << "Stock adicionado com sucesso!\n";
                } else {
                    cout << "Produto não encontrado ou quantidade inválida!\n";
                }
                pausar();
                break;
            }
            case 4: {
                limparTela();
                loja.listarProdutos();

                int id = obterInt("ID do produto: ");
                const Produto* produto = loja.buscarProduto(id);

                if (!produto) {
                    cout << "Produto com ID " << id << " não encontrado!\n";
                    pausar();
                    break;
                }

                cout << "Produto atual: " << produto->getNome()
                    << " | Preço atual: " << fixed << setprecision(2)
                    << produto->getPrecoCusto() << " EUR\n";

                float novoPreco = obterFloat("Novo preço de custo: ");

                if (loja.atualizarPrecoProduto(id, novoPreco)) {
                    cout << "Preço atualizado com sucesso!\n";
                }
                else {
                    cout << "Preço inválido!\n";
                }

                pausar();
                break;
            }
            case 5: {
                limparTela();
                loja.listarProdutos();
                int id = obterInt("ID do produto a remover: ");

                if (loja.removerProduto(id)) {
                    cout << "Produto removido com sucesso!\n";
                } else {
                    cout << "Produto não encontrado!\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

// Menu de vendas
void menuVendas(Loja& loja) {
    limparTela();
    loja.listarClientes();

    int idCliente = obterIntPositivo("ID do cliente: ");
    const Cliente* cliente = loja.buscarCliente(idCliente);

    if (!cliente) {
        cout << "Cliente não encontrado!\n";
        pausar();
        return;
    }

    int numeroFatura = loja.criarVenda(idCliente);
    if (numeroFatura == -1) {
        cout << "Erro ao criar venda!\n";
        pausar();
        return;
    }

    cout << "Venda criada com número de fatura: " << numeroFatura << endl;

    // Adicionar produtos à venda
    char continuar = 'S';
    while (continuar == 'S' || continuar == 's') {
        limparTela();
        loja.listarProdutos();

        int idProduto = obterIntPositivo("ID do produto: ");
        int quantidade = obterIntPositivo("Quantidade: ");

        if (loja.adicionarItemVenda(numeroFatura, idProduto, quantidade)) {
            cout << "Item adicionado à venda!\n";
        } else {
            cout << "Erro ao adicionar item (produto não encontrado ou stock insuficiente)!\n";
        }

        cout << "Adicionar mais produtos? (S/N): ";
        do {
            cin >> continuar;
            limparBufferEntrada();
            if (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
                cout << "Opção inválida! Digite apenas S (Sim) ou N (Não): ";
            }
        } while (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n');
    }

    // Finalizar venda
    Venda* venda = loja.buscarVenda(numeroFatura);
    if (venda && venda->getNumItens() > 0) {
        cout << "Total a pagar: " << fixed << setprecision(2)
                  << venda->getTotalComIVA() << " EUR\n";

        float valorEntregue;
        bool valorValido = false;
        
        while (!valorValido) {
            valorEntregue = obterFloat("Valor entregue pelo cliente: ");
            
            if (valorEntregue >= venda->getTotalComIVA()) {
                valorValido = true;
            } else {
                cout << "\n⚠️  VALOR INSUFICIENTE! ⚠️\n";
                cout << "Valor entregue: " << fixed << setprecision(2) << valorEntregue << "€\n";
                cout << "Valor necessário: " << fixed << setprecision(2) << venda->getTotalComIVA() << "€\n";
                cout << "Faltam: " << fixed << setprecision(2) << (venda->getTotalComIVA() - valorEntregue) << "€\n\n";
                cout << "Por favor, digite um valor igual ou superior ao total da compra.\n\n";
            }
        }

        if (loja.finalizarVenda(numeroFatura, valorEntregue)) {
            limparTela();
            venda->imprimirTalao();
            pausar();
        } else {
            cout << "Erro ao finalizar venda!\n";
            pausar();
        }
    } else {
        cout << "Nenhum item foi adicionado à venda ou venda cancelada!\n";
        pausar();
    }
}

// Menu de relatórios
void menuRelatorios(Loja& loja) {
    int opcao;
    do {
        limparTela();
        cout << "=============== RELATÓRIOS ===============\n";
        cout << "1. Relatório de Stock\n";
        cout << "2. Relatório de Vendas por Produto\n";
        cout << "3. Relatório Total de Vendas\n";
        cout << "4. Estatísticas de Vendas\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "==========================================\n";

        opcao = obterInt("Escolha uma opção: ");

        switch (opcao) {
            case 1: {
                limparTela();
                loja.relatorioStock();
                pausar();
                break;
            }
            case 2: {
                limparTela();
                cout << "Lista de produtos disponíveis para relatório:\n";
                loja.listarProdutos();

                int idProduto = obterInt("Digite o ID do produto para gerar o relatório: ");
                loja.relatorioVendasPorProduto(idProduto);
                pausar();
                break;
            }
            case 3: {
                limparTela();
                loja.relatorioTotalVendas();
                pausar();
                break;
            }
            case 4: {
                limparTela();
                loja.relatorioEstatisticasVendas();
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    // Configura a localização para UTF-8 no Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif

    // Inicializa o gerador de números aleatórios
    srand(static_cast<unsigned int>(time(nullptr)));

    Loja loja;

    int opcao;
    do {
        limparTela();
        cout << "=============== SISTEMA DE GESTÃO DE LOJA ===============\n";
        cout << "1. Efetuar Venda\n";
        cout << "2. Gestão de Clientes\n";
        cout << "3. Gestão de Produtos\n";
        cout << "4. Relatórios\n";
        cout << "0. Sair\n";
        cout << "========================================================\n";

        opcao = obterInt("Escolha uma opção: ");

        switch (opcao) {
            case 1:
                menuVendas(loja);
                break;
            case 2:
                menuClientes(loja);
                break;
            case 3:
                menuProdutos(loja);
                break;
            case 4:
                menuRelatorios(loja);
                break;
            case 0:
                cout << "Obrigado por usar o sistema!\n";
                break;
            default:
                cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);

    return 0;
}

