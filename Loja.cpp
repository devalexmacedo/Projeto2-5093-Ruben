#define _CRT_SECURE_NO_WARNINGS
#include "Loja.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

// Construtor da classe Loja
Loja::Loja() : proximoIdCliente(1), proximoIdProduto(1), proximoNumeroFatura(1000), indiceVendaAtual(0) {
    inicializarDadosIniciais();
}

int Loja::adicionarCliente(const string& nome, const string& telefone, const string& morada, const string& cidade) {
    // Validação básica dos campos
    if (nome.empty() || all_of(nome.begin(), nome.end(), ::isspace)) {
        cout << "Nome inválido. Cliente não adicionado.\n";
        return -1;
    }
    if (telefone.empty() || !all_of(telefone.begin(), telefone.end(), ::isdigit) || telefone.length() != 9) {
        cout << "Telefone inválido. Cliente não adicionado.\n";
        return -1;
    }
    if (morada.empty()) {
        cout << "Morada inválida. Cliente não adicionado.\n";
        return -1;
    }
    if (cidade.empty()) {
        cout << "Cidade inválida. Cliente não adicionado.\n";
        return -1;
    }
    // Verifica duplicidade de telefone
    auto it = find_if(clientes.begin(), clientes.end(),
        [&telefone](const Cliente& c) { return c.getTelefone() == telefone; });
    if (it != clientes.end()) {
        cout << "Já existe um cliente com esse telefone. Cliente não adicionado.\n";
        return -1;
    }
    // Cria o novo cliente e adiciona à lista
    Cliente novoCliente(nome, telefone, morada, cidade);
    novoCliente.setId(proximoIdCliente);
    clientes.push_back(novoCliente);
    cout << "Cliente adicionado com sucesso! ID: " << proximoIdCliente << "\n";
    return proximoIdCliente++;
}

// Remove um cliente pelo ID
bool Loja::removerCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });

    if (it != clientes.end()) {
        clientes.erase(it);
        return true;
    }
    return false;
}

// Altera o nome de um cliente
bool Loja::alterarNomeCliente(int id, const string& novoNome) {
    Cliente* cliente = buscarCliente(id);
    if (cliente) {
        cliente->setNome(novoNome);
        return true;
    }
    return false;
}

// Lista todos os clientes cadastrados
void Loja::listarClientes() const {
    cout << "\n";
    cout << "+=========================================================================================================+\n";
    cout << "|                                           CLIENTES CADASTRADOS                                          |\n";
    cout << "+=========================================================================================================+\n";
    cout << "\n";

    if (clientes.empty()) {
        cout << "Nenhum cliente cadastrado.\n\n";
        return;
    }

    cout << "+====+===============================+=============+=================================+===================+\n";
    cout << "| ID |             NOME              |   TELEFONE  |             MORADA              |       CIDADE      |\n";
    cout << "+====+===============================+=============+=================================+===================+\n";

    for (const auto& cliente : clientes) {
        string nomeTruncado = cliente.getNome();
        if (nomeTruncado.length() > 30) {
            nomeTruncado = nomeTruncado.substr(0, 29) + "...";
        }

        string moradaTruncada = cliente.getMorada();
        if (moradaTruncada.length() > 30) {
            moradaTruncada = moradaTruncada.substr(0, 29) + "...";
        }

        string cidadeTruncada = cliente.getCidade();
        if (cidadeTruncada.length() > 17) {
            cidadeTruncada = cidadeTruncada.substr(0, 14) + "...";
        }

        cout << "| " << right << setw(2) << cliente.getId() << " | "
            << left << setw(29) << nomeTruncado << " | "
            << left << setw(11) << cliente.getTelefone() << " | "
            << left << setw(31) << moradaTruncada << " | "
            << left << setw(17) << cidadeTruncada << " |\n";
    }

    cout << "+====+===============================+=============+=================================+===================+\n";
    cout << "\n";
}

// Adiciona um novo produto
int Loja::adicionarProduto(const string& nome, int quantidade, float precoCusto) {
    if (nome.empty() || all_of(nome.begin(),nome.end(), ::isspace)) {
        cout << "Nome inválido. Produto não adicionado.\n";
        return -1;
    }
    if (quantidade < 0) {
        cout << "Quantidade inválida. Produto não adicionado.\n";
        return -1;
    }
    if (precoCusto <= 0.0f) {
        cout << "Preço de custo inválido. Produto não adicionado.\n";
        return -1;
    }
    //Opcional: evita produtos duplicados com o mesmo nome
    auto it = find_if(produtos.begin(), produtos.end(),
        [&nome](const Produto& p) { return p.getNome() == nome; }); 
    if (it != produtos.end()) {
        cout << "Já existe um produto com esse nome. Produto não adicionado.\n";
        return -1;
    }
    
    Produto novoProduto(nome, quantidade, precoCusto);
    novoProduto.setId(proximoIdProduto);
    produtos.push_back(novoProduto);
    return proximoIdProduto++;
}

// Remove um produto pelo ID
bool Loja::removerProduto(int id) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });

    if (it != produtos.end()) {
        produtos.erase(it);
        return true;
    }
    return false;
}

// Adiciona estoque a um produto existente
bool Loja::adicionarEstoque(int id, int quantidade) {
    Produto* produto = buscarProduto(id);
    if (produto) {
        produto->adicionarEstoque(quantidade);
        return true;
    }
    return false;
}

// Atualiza o preço de custo de um produto
bool Loja::atualizarPrecoProduto(int id, float novoPrecoCusto) {
    Produto* produto = buscarProduto(id);
    if (produto && novoPrecoCusto > 0.0f) {
        produto->setPrecoCusto(novoPrecoCusto);
        return true;
    }
    return false;
}

// Lista todos os produtos em estoque
void Loja::listarProdutos() const {
    cout << "\n";
    cout << "+===============================================================================+\n";
    cout << "|                              PRODUTOS EM STOCK                                |\n";
    cout << "+===============================================================================+\n";
    cout << "\n";

    if (produtos.empty()) {
        cout << "Nenhum produto cadastrado.\n\n";
        return;
    }

    cout << "+====+========================================+=====+=============+=============+\n";
    cout << "| ID |                PRODUTO                 | QTD | PRECO UNIT. | PRECO VENDA |\n";
    cout << "+====+========================================+=====+=============+=============+\n";

    for (const auto& produto : produtos) {
        string nomeTruncado = produto.getNome();
        if (nomeTruncado.length() > 28) {
            nomeTruncado = nomeTruncado.substr(0, 25) + "...";
        }

        cout << "| " << right << setw(2) << produto.getId() << " | "
            << left << setw(38) << nomeTruncado << " | "
            << right << setw(3) << produto.getQuantidade() << " | "
            << right << setw(10) << fixed << setprecision(2) << produto.getPrecoCusto() << "€ | "
            << right << setw(10) << fixed << setprecision(2) << produto.getPrecoVenda() << "€ |\n";
    }

    cout << "+====+========================================+=====+=============+=============+\n";
    cout << "\n";
}

// Gera relatório do estoque atual
void Loja::relatorioStock() const {
    cout << "\n";
    cout << "+========================================================================+\n";
    cout << "|                           RELATORIO DE STOCK                           |\n";
    cout << "=========================================================================+\n";
    cout << "\n";

    if (produtos.empty()) {
        cout << "Nenhum produto em estoque.\n\n";
        return;
    }

    cout << "+====+==============================+=====+=============+================+\n";
    cout << "| ID |           PRODUTO            | QTD | PRECO UNIT. |  VALOR TOTAL   |\n";
    cout << "+====+==============================+=====+=============+================+\n";

    int totalQuantidade = 0;
    float valorTotalEstoque = 0.0f;

    for (const auto& produto : produtos) {
        string nomeTruncado = produto.getNome();
        if (nomeTruncado.length() > 28) {
            nomeTruncado = nomeTruncado.substr(0, 25) + "...";
        }

        // Adiciona indicador de status do estoque
        string status = "";
        if (produto.getQuantidade() == 0) {
            status = " [SEM]";
            nomeTruncado = nomeTruncado.substr(0, 23) + status;
        }
        else if (produto.getQuantidade() <= 5) {
            status = " [BAIXO]";
            nomeTruncado = nomeTruncado.substr(0, 20) + status;
        }

        float valorTotal = produto.getQuantidade() * produto.getPrecoCusto();
        totalQuantidade += produto.getQuantidade();
        valorTotalEstoque += valorTotal;


        cout << "| " << right << setw(2) << produto.getId() << " | "
            << left << setw(28) << nomeTruncado << " | "
            << right << setw(3) << produto.getQuantidade() << " | "
            << right << setw(10) << fixed << setprecision(2) << produto.getPrecoCusto() << "€ | "
            << right << setw(13) << fixed << setprecision(2) << valorTotal << "€ |\n";
    }

    cout << "+====+==============================+=====+=============+================+\n";
    cout << "|         TOTAL GERAL               | " << right << setw(3) << totalQuantidade << " |             | "
        << right << setw(13) << fixed << setprecision(2) << valorTotalEstoque << "€ |\n";
    cout << "+====+==============================+=====+=============+================+\n";
    cout << "\n";
    cout << "Legenda: [BAIXO] = Stock baixo (<=5)  [SEM] = Sem stock\n";
    cout << "\n";
}

// Cria uma nova venda
int Loja::criarVenda(int idCliente) {
    Venda novaVenda(proximoNumeroFatura, idCliente);

    // Implementa estrutura circular: quando atinge 100 vendas, sobrescreve a mais antiga
    if (static_cast<int>(vendas.size()) < MAX_VENDAS) {
        vendas.push_back(novaVenda);
        indiceVendaAtual = static_cast<int>(vendas.size()) - 1;
    }
    else {
        // Sobrescreve a venda mais antiga (estrutura circular)
        vendas[indiceVendaAtual % MAX_VENDAS] = novaVenda;
        indiceVendaAtual = (indiceVendaAtual + 1) % MAX_VENDAS;
    }

    return proximoNumeroFatura++;
}

// Adiciona um item a uma venda existente
bool Loja::adicionarItemVenda(int numeroFatura, int idProduto, int quantidade) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) return false;

    Produto* produto = buscarProduto(idProduto);
    if (!produto) return false;

    if (!produto->temEstoqueSuficiente(quantidade)) {
        return false;
    }

    venda->adicionarItem(idProduto, produto->getNome(), quantidade, produto->getPrecoCusto());
    produto->removerEstoque(quantidade);
    return true;
}

// Finaliza uma venda processando o pagamento
bool Loja::finalizarVenda(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) return false;

    if (!venda->exibirCheckout()) {
        return false; // Venda cancelada
    }

    venda->processarPagamento(valorEntregue);
    venda->imprimirTalao();
    return true;
}

// Finaliza uma venda sem exibir checkout (para vendas iniciais)
bool Loja::finalizarVendaSilenciosa(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) return false;

    venda->processarPagamento(valorEntregue);
    return true;
}

// Gera relatório de vendas por produto
void Loja::relatorioVendasPorProduto(int idProduto) const {
    const Produto* produto = buscarProduto(idProduto);
    if (!produto) {
        cout << "Produto não encontrado!\n";
        return;
    }

    cout << "\n";
    cout << "+==============================================================================+\n";
    cout << "|                      RELATORIO DE VENDAS POR PRODUTO                         |\n";
    cout << "+==============================================================================+\n";
    cout << "Produto: " << produto->getNome() << " (ID: " << idProduto << ")\n";
    cout << "\n";

    cout << "+===========+==================+==========+==========+=========================+\n";
    cout << "| FATURA N° |       DATA       | CLIENTE  |   QTD    |      VALOR TOTAL        |\n";
    cout << "+===========+==================+==========+==========+=========================+\n";

    int totalQuantidade = 0;
    float valorTotal = 0.0f;
    int totalVendas = 0;

    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            for (int i = 0; i < venda.getNumItens(); i++) {
                const ItemVenda* item = venda.getItem(i);
                if (item && item->idProduto == idProduto) {
                    cout << "| " << right << setw(9) << venda.getNumeroFatura() << " | "
                        << left << setw(14) << venda.getData() << " | "
                        << right << setw(8) << venda.getNumeroCliente() << " | "
                        << right << setw(8) << item->quantidade << " | "
                        << right << setw(18) << fixed << setprecision(2) << item->total << "€     |\n";

                    totalQuantidade += item->quantidade;
                    valorTotal += item->total;
                    totalVendas++;
                }
            }
        }
    }
    cout << "+===========+==================+==========+==========+=========================+\n";
    if (totalVendas == 0) {
        cout << "|                          NENHUMA VENDA REGISTRADA                            |\n";
    }
    else {
        cout << "+==================================+====================+======================+\n";
        cout << "|   TOTAL DE VENDAS REALIZADAS     | QTD TOTAL VENDIDA  |      VALOR TOTAL     |\n";
        cout << "+==================================+====================+======================+\n";
        cout << right << setw(34) << totalVendas << " | "
            << right << setw(18) << totalQuantidade << " | "
            << right << setw(19) << fixed << setprecision(2) << valorTotal << "€ |\n";
    }

    cout << "+==================================+====================+======================+\n";
    cout << "\n";
}

// Gera relatório total de vendas
void Loja::relatorioTotalVendas() const {
    cout << "\n";
    cout << "+==============================================================================+\n";
    cout << "|                          RELATORIO TOTAL DE VENDAS                           |\n";
    cout << "+==============================================================================+\n";
    cout << "\n";

    cout << "+===========+==================+===========+==========+========================+\n";
    cout << "| FATURA N° |       DATA       |  CLIENTE  |  ITENS   |    VALOR POR FATURA    |\n";
    cout << "+===========+==================+===========+==========+========================+\n";

    int totalVendas = 0;
    float valorTotalGeral = 0.0f;

    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            cout << "| " << right << setw(10) << venda.getNumeroFatura() << " | "
                << left << setw(14) << venda.getData() << " | "
                << right << setw(8) << venda.getNumeroCliente() << " | "
                << right << setw(8) << venda.getNumItens() << " | "
                << right << setw(21) << fixed << setprecision(2) << venda.getTotalComIVA() << "€ |\n";

            totalVendas++;
            valorTotalGeral += venda.getTotalComIVA();
        }
    }
    cout << "+===========+==================+===========+==========+========================+\n";

    if (totalVendas == 0) {
        cout << "|                          NENHUMA VENDA REGISTRADA                            |\n";
    }
    else {
        cout << "+===========+=============================+=============+======================+\n";
        cout << "|   TOTAL   | " << totalVendas << " vendas realizadas         | VALOR TOTAL |" 
            << right << setw(20) << fixed << setprecision(2) << valorTotalGeral << "€ |\n";
    }

    cout << "+===========+=============================+=============+======================+\n";
    cout << "\n";
}

// Gera relatório de estatísticas de vendas (produto mais/menos vendido, lucros, melhor cliente)
void Loja::relatorioEstatisticasVendas() const {
    cout << "\n";
    cout << "+=======================================================================================+\n";
    cout << "|                            ESTATISTICAS DE VENDAS                                    |\n";
    cout << "+=======================================================================================+\n";
    cout << "\n";

    // Mapas para armazenar estatísticas
    map<int, int> quantidadePorProduto;
    map<int, float> valorPorProduto;
    map<int, float> lucroPorProduto;
    map<int, float> valorPorCliente;

    // Coleta dados de todas as vendas
    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            // Soma valor por cliente
            valorPorCliente[venda.getNumeroCliente()] += venda.getTotalComIVA();

            // Processa cada item da venda
            for (int i = 0; i < venda.getNumItens(); i++) {
                const ItemVenda* item = venda.getItem(i);
                if (item) {
                    quantidadePorProduto[item->idProduto] += item->quantidade;
                    valorPorProduto[item->idProduto] += item->total;

                    // Calcula lucro (preço venda - preço custo) * quantidade
                    const Produto* produto = buscarProduto(item->idProduto);
                    if (produto) {
                        float lucroUnitario = produto->getPrecoVenda() - produto->getPrecoCusto();
                        lucroPorProduto[item->idProduto] += lucroUnitario * item->quantidade;
                    }
                }
            }
        }
    }

    if (quantidadePorProduto.empty()) {
        cout << "Nenhuma venda registrada para gerar estatisticas.\n\n";
        return;
    }

    // Encontra produto mais vendido
    int produtoMaisVendido = 0;
    int maiorQuantidade = 0;
    for (const auto& par : quantidadePorProduto) {
        if (par.second > maiorQuantidade) {
            maiorQuantidade = par.second;
            produtoMaisVendido = par.first;
        }
    }

    // Encontra produto menos vendido
    int produtoMenosVendido = 0;
    int menorQuantidade = INT_MAX;
    for (const auto& par : quantidadePorProduto) {
        if (par.second < menorQuantidade) {
            menorQuantidade = par.second;
            produtoMenosVendido = par.first;
        }
    }

    // Encontra cliente que mais comprou
    int melhorCliente = 0;
    float maiorValorCliente = 0.0f;
    for (const auto& par : valorPorCliente) {
        if (par.second > maiorValorCliente) {
            maiorValorCliente = par.second;
            melhorCliente = par.first;
        }
    }

    // Exibe resultados
    cout << "+=======================================================================================+\n";
    cout << "|                                 PRODUTO MAIS VENDIDO                                  |\n";
    cout << "+=======================================================================================+\n";
    const Produto* prodMaisVendido = buscarProduto(produtoMaisVendido);
    if (prodMaisVendido) {
        cout << "Produto: " << prodMaisVendido->getNome() << " (ID: " << produtoMaisVendido << ")\n";
        cout << "Quantidade vendida: " << maiorQuantidade << " unidades\n";
        cout << "Valor total vendido: " << fixed << setprecision(2) << valorPorProduto[produtoMaisVendido] << "€\n";
        cout << "Lucro gerado: " << fixed << setprecision(2) << lucroPorProduto[produtoMaisVendido] << "€\n";
    }
    cout << "\n";

    cout << "+=======================================================================================+\n";
    cout << "|                                PRODUTO MENOS VENDIDO                                  |\n";
    cout << "+=======================================================================================+\n";
    const Produto* prodMenosVendido = buscarProduto(produtoMenosVendido);
    if (prodMenosVendido) {
        cout << "Produto: " << prodMenosVendido->getNome() << " (ID: " << produtoMenosVendido << ")\n";
        cout << "Quantidade vendida: " << menorQuantidade << " unidades\n";
        cout << "Valor total vendido: " << fixed << setprecision(2) << valorPorProduto[produtoMenosVendido] << "€\n";
    }
    cout << "\n";

    cout << "+=======================================================================================+\n";
    cout << "|                               CLIENTE QUE MAIS COMPROU                                |\n";
    cout << "+=======================================================================================+\n";
    const Cliente* clienteTop = buscarCliente(melhorCliente);
    if (clienteTop) {
        cout << "Cliente: " << clienteTop->getNome() << " (ID: " << melhorCliente << ")\n";
        cout << "Valor total comprado: " << fixed << setprecision(2) << maiorValorCliente << "€\n";
        cout << "Telefone: " << clienteTop->getTelefone() << "\n";
    }
    cout << "\n";

    cout << "+=======================================================================================+\n";
    cout << "|                                      RESUMO GERAL                                     |\n";
    cout << "+=======================================================================================+\n";
    cout << "Total de produtos diferentes vendidos: " << static_cast<int>(quantidadePorProduto.size()) << "\n";
    cout << "Total de clientes ativos: " << static_cast<int>(valorPorCliente.size()) << "\n";

    float lucroTotal = 0.0f;
    for (const auto& par : lucroPorProduto) {
        lucroTotal += par.second;
    }
    cout << "Lucro total gerado: " << fixed << setprecision(2) << lucroTotal << "€\n";
    cout << "\n";
}

// Inicializa a loja com dados de exemplo
void Loja::inicializarDadosIniciais() {
    // Adicionar clientes iniciais
    adicionarCliente("Joao Silva", "912345678", "Rua das Flores, 123", "Lisboa");
    adicionarCliente("Maria Santos", "923456789", "Av. da Liberdade, 456", "Porto");
    adicionarCliente("Pedro Costa", "934567890", "Rua do Comercio, 789", "Coimbra");
    adicionarCliente("Ana Rodrigues", "945678901", "Praca da Republica, 321", "Braga");
    adicionarCliente("Carlos Mendes", "956789012", "Rua Central, 654", "Faro");
    adicionarCliente("Sofia Pereira", "967890123", "Av. dos Aliados, 987", "Aveiro");
    adicionarCliente("Miguel Ferreira", "978901234", "Rua da Paz, 147", "Viseu");
    adicionarCliente("Catarina Lopes", "989012345", "Largo do Municipio, 258", "Evora");

    // Adicionar produtos iniciais
    adicionarProduto("Placa Mae ASUS B450", 15, 89.99f);
    adicionarProduto("Processador AMD Ryzen 5", 12, 199.99f);
    adicionarProduto("Memoria RAM 16GB DDR4", 25, 79.99f);
    adicionarProduto("Disco SSD 1TB NVMe", 20, 87.94f);
    adicionarProduto("Placa Grafica RTX 3060", 8, 399.99f);
    adicionarProduto("Fonte 650W 80+ Bronze", 18, 71.95f);
    adicionarProduto("Caixa ATX Mid Tower", 10, 59.99f);
    adicionarProduto("Monitor 24'' Full HD", 15, 143.91f);
    adicionarProduto("Teclado Mecanico RGB", 25, 89.99f);
    adicionarProduto("Cooler CPU", 30, 29.99f);

    // Criar vendas iniciais
    criarVendasIniciais();
}

// Função auxiliar para criar vendas iniciais
void Loja::criarVendasIniciais() {
    // Venda 1: João Silva
    int fatura1 = criarVenda(1);
    adicionarItemVenda(fatura1, 1, 1); // Placa Mãe
    adicionarItemVenda(fatura1, 2, 1); // Processador
    adicionarItemVenda(fatura1, 3, 2); // 2x RAM
    finalizarVendaSilenciosa(fatura1, 500.0f);

    // Venda 2: Maria Santos
    int fatura2 = criarVenda(2);
    adicionarItemVenda(fatura2, 8, 1); // Monitor
    adicionarItemVenda(fatura2, 7, 1); // Caixa
    finalizarVendaSilenciosa(fatura2, 250.0f);

    // Venda 3: Pedro Costa
    int fatura3 = criarVenda(3);
    adicionarItemVenda(fatura3, 4, 2); // 2x SSD
    adicionarItemVenda(fatura3, 6, 1); // Fonte
    finalizarVendaSilenciosa(fatura3, 300.0f);

    // Venda 4: Ana Rodrigues
    int fatura4 = criarVenda(4);
    adicionarItemVenda(fatura4, 5, 1); // Placa Gráfica RTX 3060
    finalizarVendaSilenciosa(fatura4, 520.0f);

    // Venda 5: Carlos Mendes
    int fatura5 = criarVenda(5);
    adicionarItemVenda(fatura5, 7, 1); // Caixa
    adicionarItemVenda(fatura5, 10, 2); // 2x Cooler
    finalizarVendaSilenciosa(fatura5, 150.0f);
}

// Busca um cliente pelo ID (versão const)
const Cliente* Loja::buscarCliente(int id) const {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });
    return (it != clientes.end()) ? &(*it) : nullptr;
}

// Busca um cliente pelo ID (versão não-const)
Cliente* Loja::buscarCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });
    return (it != clientes.end()) ? &(*it) : nullptr;
}

// Busca um produto pelo ID (versão const)
const Produto* Loja::buscarProduto(int id) const {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });
    return (it != produtos.end()) ? &(*it) : nullptr;
}

// Busca um produto pelo ID (versão não-const)
Produto* Loja::buscarProduto(int id) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });
    return (it != produtos.end()) ? &(*it) : nullptr;
}

// Busca uma venda pelo número da fatura (versão const)
const Venda* Loja::buscarVenda(int numeroFatura) const {
    auto it = find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });
    return (it != vendas.end()) ? &(*it) : nullptr;
}

// Busca uma venda pelo número da fatura (versão não-const)
Venda* Loja::buscarVenda(int numeroFatura) {
    auto it = find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });
    return (it != vendas.end()) ? &(*it) : nullptr;
}



