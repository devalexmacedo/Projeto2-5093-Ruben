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

using namespace std;

// Função auxiliar para limpar o buffer de entrada
void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Função para tratar entrada inválida
void tratarErroEntrada() {
    std::cout << "Entrada inválida. Por favor, tente novamente.\n";
    std::cin.clear();
    limparBufferEntrada();
}

// Função para obter um int válido do usuário
int obterInt(const string& prompt) {
    int n;
    string entrada;

    while (true) {
        cout << prompt;
        getline(cin, entrada);
        stringstream ss(entrada);

        if (ss >> n && ss.eof()) {  // Sucesso se leu um int e não sobrou mais nada
            return n;
        }
        else {
            tratarErroEntrada(); // Usa suas funções já existentes
        }
    }
}

// Função para obter um float válido do usuário
float obterFloat(const std::string& prompt) {
    string entrada;
    float valor;

    while (true) {
        cout << prompt;
        getline(cin, entrada);

        // Substitui vírgula por ponto
        std::replace(entrada.begin(), entrada.end(), ',', '.');

        stringstream ss(entrada);
        if (ss >> valor && ss.eof() && valor > 0) {
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

// Função para obter uma string válida do usuário
std::string obterString(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);
    return valor;
}

#ifdef _WIN32
    #include <conio.h>
    #define GETCH() _getch()
#else
    #include <termios.h>
    #include <unistd.h>
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

// Função para pausar e aguardar tecla
void pausar() {
    std::cout << "\nPressione qualquer tecla para continuar...";
    _getch();
}

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Implementação dos menus
void menuClientes(Loja& loja) {
    int opcao;
    do {
        limparTela();
        std::cout << "=============== GESTÃO DE CLIENTES ===============\n";
        std::cout << "1. Listar Clientes\n";
        std::cout << "2. Adicionar Cliente\n";
        std::cout << "3. Alterar Nome do Cliente\n";
        std::cout << "4. Remover Cliente\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "==================================================\n";
        
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
                std::string nome = obterString("Nome do cliente: ");
                std::string telefone = obterString("Telefone: ");
                std::string morada = obterString("Morada: ");
                
                int id = loja.adicionarCliente(nome, telefone, morada);
                std::cout << "Cliente adicionado com ID: " << id << std::endl;
                pausar();
                break;
            }
            case 3: {
                limparTela();
                loja.listarClientes();
                int id = obterInt("ID do cliente a alterar: ");
                std::string novoNome = obterString("Novo nome: ");
                
                if (loja.alterarNomeCliente(id, novoNome)) {
                    std::cout << "Nome alterado com sucesso!\n";
                } else {
                    std::cout << "Cliente não encontrado!\n";
                }
                pausar();
                break;
            }
            case 4: {
                limparTela();
                loja.listarClientes();
                int id = obterInt("ID do cliente a remover: ");
                
                if (loja.removerCliente(id)) {
                    std::cout << "Cliente removido com sucesso!\n";
                } else {
                    std::cout << "Cliente não encontrado!\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

void menuProdutos(Loja& loja) {
    int opcao;
    do {
        limparTela();
        std::cout << "=============== GESTÃO DE PRODUTOS ===============\n";
        std::cout << "1. Listar Produtos\n";
        std::cout << "2. Adicionar Produto\n";
        std::cout << "3. Adicionar Stock\n";
        std::cout << "4. Atualizar Preço\n";
        std::cout << "5. Remover Produto\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "==================================================\n";
        
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
                std::string nome = obterString("Nome do produto: ");
                int quantidade = obterInt("Quantidade inicial: ");
                float precoCusto = obterFloat("Preço de custo: ");
                
                int id = loja.adicionarProduto(nome, quantidade, precoCusto);
                std::cout << "Produto adicionado com ID: " << id << std::endl;
                pausar();
                break;
            }
            case 3: {
                limparTela();
                loja.listarProdutos();
                int id = obterInt("ID do produto: ");
                int quantidade = obterInt("Quantidade a adicionar: ");
                
                if (loja.adicionarEstoqueProduto(id, quantidade)) {
                    std::cout << "Stock adicionado com sucesso!\n";
                } else {
                    std::cout << "Produto não encontrado ou quantidade inválida!\n";
                }
                pausar();
                break;
            }
            case 4: {
                limparTela();
                loja.listarProdutos();

                int id = obterInt("ID do produto: ");
                Produto* produto = loja.buscarProduto(id);

                if (!produto) {
                    std::cout << "Produto com ID " << id << " não encontrado!\n";
                    pausar();
                    break;
                }

                std::cout << "Produto atual: " << produto->getNome()
                    << " | Preço atual: " << std::fixed << std::setprecision(2)
                    << produto->getPrecoCusto() << " EUR\n";

                float novoPreco = obterFloat("Novo preço de custo: ");

                if (loja.atualizarPrecoProduto(id, novoPreco)) {
                    std::cout << "Preço atualizado com sucesso!\n";
                }
                else {
                    std::cout << "Preço inválido!\n";
                }

                pausar();
                break;
            }
            case 5: {
                limparTela();
                loja.listarProdutos();
                int id = obterInt("ID do produto a remover: ");
                
                if (loja.removerProduto(id)) {
                    std::cout << "Produto removido com sucesso!\n";
                } else {
                    std::cout << "Produto não encontrado!\n";
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

void menuVendas(Loja& loja) {
    limparTela();
    loja.listarClientes();
    
    int idCliente = obterInt("ID do cliente: ");
    Cliente* cliente = loja.buscarCliente(idCliente);
    
    if (!cliente) {
        std::cout << "Cliente não encontrado!\n";
        pausar();
        return;
    }
    
    int numeroFatura = loja.criarVenda(idCliente);
    if (numeroFatura == -1) {
        std::cout << "Erro ao criar venda!\n";
        pausar();
        return;
    }
    
    std::cout << "Venda criada com número de fatura: " << numeroFatura << std::endl;
    
    // Adicionar produtos à venda
    char continuar = 'S';
    while (continuar == 'S' || continuar == 's') {
        limparTela();
        loja.listarProdutos();
        
        int idProduto = obterInt("ID do produto: ");
        int quantidade = obterInt("Quantidade: ");
        
        if (loja.adicionarItemVenda(numeroFatura, idProduto, quantidade)) {
            std::cout << "Item adicionado à venda!\n";
        } else {
            std::cout << "Erro ao adicionar item (produto não encontrado ou stock insuficiente)!\n";
        }
        
        std::cout << "Adicionar mais produtos? (S/N): ";
        std::cin >> continuar;
        limparBufferEntrada();
    }
    
    // Finalizar venda
    Venda* venda = loja.buscarVenda(numeroFatura);
    if (venda && venda->getNumItens() > 0) {
        std::cout << "Total a pagar: " << std::fixed << std::setprecision(2) 
                  << venda->getTotalComIVA() << " EUR\n";
        
        float valorEntregue = obterFloat("Valor entregue pelo cliente: ");
        
        if (loja.finalizarVenda(numeroFatura, valorEntregue)) {
            limparTela();
            venda->imprimirTalao();
            pausar();
        } else {
            std::cout << "Valor insuficiente!\n";
            pausar();
        }
    } else {
        std::cout << "Nenhum item foi adicionado à venda!\n";
        pausar();
    }
}

void menuRelatorios(Loja& loja) {
    int opcao;
    do {
        limparTela();
        std::cout << "=============== RELATÓRIOS ===============\n";
        std::cout << "1. Relatório de Stock\n";
        std::cout << "2. Relatório de Vendas por Produto\n";
        std::cout << "3. Relatório Total de Vendas\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "==========================================\n";
        
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
                std::string nomeProduto = obterString("Nome do produto: ");
                loja.relatorioVendasPorProduto(nomeProduto);
                pausar();
                break;
            }
            case 3: {
                limparTela();
                loja.relatorioTotalVendas();
                pausar();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

int main() {
    // Configurar localização para português
    #ifdef _WIN32
        system("chcp 65001 > nul"); // UTF-8 no Windows
    #endif
    
    // Inicializar gerador de números aleatórios
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Criar instância da loja
    Loja loja;
    
    int opcao;
    do {
        limparTela();
        std::cout << "=============== SISTEMA DE GESTÃO DE LOJA ===============\n";
        std::cout << "1. Efetuar Venda\n";
        std::cout << "2. Gestão de Clientes\n";
        std::cout << "3. Gestão de Produtos\n";
        std::cout << "4. Relatórios\n";
        std::cout << "0. Sair\n";
        std::cout << "========================================================\n";
        
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
                std::cout << "Obrigado por usar o sistema!\n";
                break;
            default:
                std::cout << "Opção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
    
    return 0;
}

