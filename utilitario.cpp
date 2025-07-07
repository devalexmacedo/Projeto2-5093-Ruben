// utilitario.cpp
#include "utilitario.h"
#include "Loja.h"     // Incluir Loja.h novamente aqui não causa problema por causa dos include guards
#include "Cliente.h"
#include "Produto.h"
#include "Venda.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// Implementações das funções utilitárias

void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void tratarErroEntrada() {
    std::cout << "Entrada inválida. Por favor, tente novamente.\n";
    std::cin.clear();
    limparBufferEntrada();
}

int obterInt(const std::string& prompt) {
    int n;
    std::string entrada;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, entrada);

        if (entrada.empty()) {
            std::cout << "Entrada inválida. Por favor, digite um número.\n";
            continue;
        }

        std::stringstream ss(entrada);
        if (ss >> n && ss.eof() && n >= 0) {
            return n;
        }
        else {
            std::cout << "Entrada inválida. Por favor, digite apenas números inteiros positivos.\n";
        }
    }
}

int obterIntPositivo(const std::string& prompt) {
    int n;
    std::string entrada;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, entrada);

        if (entrada.empty()) {
            std::cout << "Entrada inválida. Por favor, digite um número.\n";
            continue;
        }

        std::stringstream ss(entrada);
        if (ss >> n && ss.eof() && n > 0) {
            return n;
        }
        else {
            std::cout << "Entrada inválida. Por favor, digite apenas números inteiros maiores que 0.\n";
        }
    }
}

float obterFloat(const std::string& prompt) {
    std::string entrada;
    float valor;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, entrada);

        if (entrada.empty()) {
            std::cout << "Entrada inválida. Por favor, digite um valor.\n";
            continue;
        }

        std::replace(entrada.begin(), entrada.end(), ',', '.');

        std::stringstream ss(entrada);
        if (ss >> valor && ss.eof() && valor >= 0) {
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

std::string obterString(const std::string& prompt) {
    std::string valor;
    std::cout << prompt;
    std::getline(std::cin, valor);
    return valor;
}

void pausar() {
    std::cout << "\nPressione qualquer tecla para continuar...";
    (void)GETCH();
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Implementações das funções de validação
bool validarNome(const std::string& nome) {
    if (nome.empty() || nome.length() > 20) {
        return false;
    }
    for (char c : nome) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool validarTelefone(const std::string& telefone) {
    if (telefone.length() != 9) {
        return false;
    }
    for (char c : telefone) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool validarMorada(const std::string& morada) {
    if (morada.empty()) {
        return false;
    }
    for (char c : morada) {
        if (!std::isalnum(c) && c != ' ' && c != ',' && c != '.' && c != '-') {
            return false;
        }
    }
    return true;
}

bool validarCidade(const std::string& cidade) {
    if (cidade.empty()) {
        return false;
    }
    for (char c : cidade) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// Implementações das funções para obter entrada validada
std::string obterNomeValido(const std::string& prompt) {
    std::string valor;
    do {
        valor = obterString(prompt);
        if (!validarNome(valor)) {
            std::cout << "Erro: Nome inválido. Não pode ser vazio, máximo 20 caracteres e só pode conter letras.\n";
        }
    } while (!validarNome(valor));
    return valor;
}

std::string obterTelefoneValido(const std::string& prompt) {
    std::string valor;
    do {
        valor = obterString(prompt);
        if (!validarTelefone(valor)) {
            std::cout << "Erro: Telefone inválido. Deve conter exatamente 9 dígitos numéricos.\n";
        }
    } while (!validarTelefone(valor));
    return valor;
}

std::string obterMoradaValida(const std::string& prompt) {
    std::string valor;
    do {
        valor = obterString(prompt);
        if (!validarMorada(valor)) {
            std::cout << "Erro: Morada inválida. Não pode ser vazia e não deve conter símbolos (exceto vírgula).\n";
        }
    } while (!validarMorada(valor));
    return valor;
}

std::string obterCidadeValida(const std::string& prompt) {
    std::string valor;
    do {
        valor = obterString(prompt);
        if (!validarCidade(valor)) {
            std::cout << "Erro: Cidade inválida. Só pode conter letras.\n";
        }
    } while (!validarCidade(valor));
    return valor;
}

// Implementação da função auxiliar de comparação de strings
bool compararStringsIgnorarCase(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) {
        return false;
    }
    return std::equal(s1.begin(), s1.end(), s2.begin(),
        [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

// Implementações das funções de Menu
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
            string nome = obterNomeValido("Nome do cliente: ");
            string telefone = obterTelefoneValido("Telefone: ");
            string morada = obterMoradaValida("Morada: ");
            string cidade = obterCidadeValida("Cidade: ");

            int id = loja.adicionarCliente(nome, telefone, morada, cidade);
            if (id != -1) {
                cout << "Cliente adicionado com ID: " << id << endl;
            }
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
            }
            else {
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
            }
            else {
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
            string nomeProdutoDigitado;
            char confirmacaoNome;

            do {
                nomeProdutoDigitado = obterString("Nome do produto: ");

                cout << "Voce digitou: '" << nomeProdutoDigitado << "'\n";
                cout << "O nome esta correto? (S/N): ";
                cin >> confirmacaoNome;
                limparBufferEntrada();

                confirmacaoNome = toupper(confirmacaoNome);
                if (confirmacaoNome == 'N') {
                    cout << "Por favor, digite o nome novamente.\n";
                    pausar();
                    limparTela();
                }
                else if (confirmacaoNome != 'S') {
                    cout << "Opcao invalida. Por favor, digite 'S' para sim ou 'N' para nao.\n";
                    pausar();
                    limparTela();
                }
            } while (confirmacaoNome != 'S');

            // Normaliza o nome para a busca (se a sua busca for case-insensitive)
            string nomeParaBusca = nomeProdutoDigitado;
            transform(nomeParaBusca.begin(), nomeParaBusca.end(), nomeParaBusca.begin(), ::tolower);

            Produto* produtoExistente = loja.buscarProdutoPorNome(nomeParaBusca);

            if (produtoExistente) {
                // --- PRODUTO JÁ CADASTRADO: Exibir detalhes e perguntar sobre atualização ---
                cout << "\nProduto com o nome '" << produtoExistente->getNome() << "' ja cadastrado:\n";
                cout << "  ID: " << produtoExistente->getId() << "\n";
                cout << "  Quantidade em estoque: " << produtoExistente->getQuantidade() << "\n";
                cout << "  Preco de custo: " << fixed << setprecision(2) << produtoExistente->getPrecoCusto() << "€\n";

                char respostaAtualizar = ' ';
                while (respostaAtualizar != 'S' && respostaAtualizar != 'N') {
                    cout << "Deseja adicionar mais ao estoque e/ou atualizar o preco? (S/N): ";
                    cin >> respostaAtualizar;
                    respostaAtualizar = toupper(respostaAtualizar);
                    limparBufferEntrada();
                }

                if (respostaAtualizar == 'S') {
                    int qtdAdicional = obterIntPositivo("Quantidade a adicionar ao estoque (0 para nao adicionar): ");
                    float novoPreco = obterFloat("Novo preco de custo (0.00 para nao atualizar): ");

                    // Chama o método 'atualizarProduto' da loja
                    if (loja.atualizarProduto(produtoExistente->getNome(), qtdAdicional, novoPreco)) {
                        cout << "\nProduto '" << produtoExistente->getNome() << "' (ID: " << produtoExistente->getId() << ") atualizado com sucesso!\n";
                    }
                    else {
                        cout << "\nHouve um erro ao atualizar o produto.\n"; // Isto pode ocorrer se o produto for removido noutro thread ou similar
                    }
                }
                else {
                    cout << "\nOperacao de atualizacao de produto cancelada.\n";
                }
            }
            else {
                // --- NOVO PRODUTO: Pedir quantidade e preço de custo para NOVO produto ---
                cout << "\nProduto '" << nomeProdutoDigitado << "' nao encontrado. Sera adicionado como um novo produto.\n";
                int quantidadeInicial = obterIntPositivo("Quantidade inicial: ");
                float precoCusto = obterFloat("Preco de custo: ");

                // Chama o método 'adicionarNovoProduto' da loja
                int novoId = loja.adicionarNovoProduto(nomeProdutoDigitado, quantidadeInicial, precoCusto);
                if (novoId != -1) {
                    cout << "\nProduto '" << nomeProdutoDigitado << "' adicionado com sucesso! ID: " << novoId << "\n";
                }
                else {
                    cout << "\nHouve um erro ao adicionar o novo produto. Verifique a quantidade/preco.\n";
                }
            }
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
            }
            else {
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
            }
            else {
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

    char continuar = 'S';
    while (continuar == 'S' || continuar == 's') {
        limparTela();
        loja.listarProdutos();

        int idProduto = obterIntPositivo("ID do produto: ");
        int quantidade = obterIntPositivo("Quantidade: ");

        if (loja.adicionarItemVenda(numeroFatura, idProduto, quantidade)) {
            cout << "Item adicionado à venda!\n";
        }
        else {
            cout << "Erro ao adicionar item (produto não encontrado ou stock insuficiente)!\n";
        }

        cout << "Adicionar mais produtos ao carrinho? (S/N): ";
        do {
            cin >> continuar;
            limparBufferEntrada();
            if (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n') {
                cout << "Opção inválida! Digite apenas S (Sim) ou N (Não): ";
            }
        } while (continuar != 'S' && continuar != 's' && continuar != 'N' && continuar != 'n');
    }

    Venda* venda = loja.buscarVenda(numeroFatura);
    if (venda && venda->getNumItens() > 0) {
        cout << "Total a pagar: " << fixed << setprecision(2)
            << venda->getTotalComIVA() << " EUR\n";

        float valorEntregue;
        bool valorValido = false;

        while (!valorValido) {
            valorEntregue = obterFloat("Valor entregue pelo cliente: ");

            constexpr float EPSILON = 0.01f;
            if (valorEntregue >= venda->getTotalComIVA() - EPSILON) {
                valorValido = true;
            }
            else {
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
        }
        else {
            cout << "Erro ao finalizar venda!\n";
            pausar();
        }
    }
    else {
        cout << "Nenhum item foi adicionado à venda ou venda cancelada!\n";
        pausar();
    }
}

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