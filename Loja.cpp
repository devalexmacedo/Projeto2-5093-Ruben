#define _CRT_SECURE_NO_WARNINGS
#include "Loja.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <map>
#include <limits>

using namespace std;

// Construtor da classe Loja
Loja::Loja() {
    proximoIdCliente = 1;
    proximoIdProduto = 1;
    proximoNumeroFatura = 1001;
    indiceVendaAtual = 0;

    inicializarDadosIniciais();
}

// Busca um cliente pelo ID (versão não-const)
Cliente* Loja::buscarCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });

    return (it != clientes.end()) ? &(*it) : nullptr;
}

// Busca um cliente pelo ID (versão const)
const Cliente* Loja::buscarCliente(int id) const {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });

    return (it != clientes.end()) ? &(*it) : nullptr;
}

// Busca um produto pelo ID (versão não-const)
Produto* Loja::buscarProduto(int id) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });

    return (it != produtos.end()) ? &(*it) : nullptr;
}

// Busca um produto pelo ID (versão const)
const Produto* Loja::buscarProduto(int id) const {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });

    return (it != produtos.end()) ? &(*it) : nullptr;
}

// Busca uma venda pelo número da fatura (versão não-const)
Venda* Loja::buscarVenda(int numeroFatura) {
    auto it = find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });

    return (it != vendas.end()) ? &(*it) : nullptr;
}

// Busca uma venda pelo número da fatura (versão const)
const Venda* Loja::buscarVenda(int numeroFatura) const {
    auto it = find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });

    return (it != vendas.end()) ? &(*it) : nullptr;
}

// Adiciona um novo cliente à loja
int Loja::adicionarCliente(const string& nome, const string& telefone, const string& morada) {
    Cliente novoCliente(nome, telefone, morada);
    novoCliente.setId(proximoIdCliente);
    clientes.push_back(novoCliente);
    return proximoIdCliente++;
}

// Remove um cliente da loja pelo ID
bool Loja::removerCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });

    if (it != clientes.end()) {
        clientes.erase(it);
        return true;
    }
    return false;
}

// Altera o nome de um cliente existente
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
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                    CLIENTES CADASTRADOS                                     ║\n";
    cout << "╠══════╦══════════════════════════════════╦═══════════════╦═══════════════════════════════════╣\n";
    cout << "║  ID  ║               NOME               ║   TELEFONE    ║             MORADA                ║\n";
    cout << "╠══════╬══════════════════════════════════╬═══════════════╬═══════════════════════════════════╣\n";

    for (const auto& cliente : clientes) {
        string nomeTruncado = cliente.getNome();
        if (nomeTruncado.length() > 32) {
            nomeTruncado = nomeTruncado.substr(0, 29) + "...";
        }
        
        string moradaTruncada = cliente.getMorada();
        if (moradaTruncada.length() > 33) {
            moradaTruncada = moradaTruncada.substr(0, 30) + "...";
        }

        cout << "║ " << right << setw(4) << cliente.getId() << " ║ "
             << left << setw(32) << nomeTruncado << " ║ "
             << left << setw(13) << cliente.getTelefone() << " ║ "
             << left << setw(33) << moradaTruncada << " ║\n";
    }

    cout << "╚══════╩══════════════════════════════════╩═══════════════╩═══════════════════════════════════╝\n";
    cout << "\n";
}

// Adiciona um novo produto à loja
int Loja::adicionarProduto(const string& nome, int quantidade, float precoCusto) {
    Produto novoProduto(nome, quantidade, precoCusto);
    novoProduto.setId(proximoIdProduto);
    produtos.push_back(novoProduto);
    return proximoIdProduto++;
}

// Remove um produto da loja pelo ID
bool Loja::removerProduto(int id) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });

    if (it != produtos.end()) {
        produtos.erase(it);
        return true;
    }
    return false;
}

// Adiciona quantidade ao estoque de um produto
bool Loja::adicionarEstoqueProduto(int id, int quantidade) {
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
    if (produto) {
        produto->setPrecoCusto(novoPrecoCusto);
        return true;
    }
    return false;
}

// Lista todos os produtos em estoque
void Loja::listarProdutos() const {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                PRODUTOS EM STOCK                                    ║\n";
    cout << "╠══════╦══════════════════════════════════╦═══════╦═══════════════╦═══════════════════╣\n";
    cout << "║  ID  ║           PRODUTO                ║  QTD  ║  PREÇO UNIT.  ║   PREÇO VENDA     ║\n";
    cout << "╠══════╬══════════════════════════════════╬═══════╬═══════════════╬═══════════════════╣\n";

    for (const auto& produto : produtos) {
        string nomeTruncado = produto.getNome();
        if (nomeTruncado.length() > 32) {
            nomeTruncado = nomeTruncado.substr(0, 29) + "...";
        }

        cout << "║ " << right << setw(4) << produto.getId() << " ║ "
             << left << setw(32) << nomeTruncado << " ║ "
             << right << setw(5) << produto.getQuantidade() << " ║ "
             << right << setw(12) << fixed << setprecision(2) << produto.getPrecoCusto() << "€ ║ "
             << right << setw(16) << fixed << setprecision(2) << produto.getPrecoVenda() << "€ ║\n";
    }

    cout << "╚══════╩══════════════════════════════════╩═══════╩═══════════════╩═══════════════════╝\n";
    cout << "\n";
}

// Cria uma nova venda
int Loja::criarVenda(int idCliente) {
    if (indiceVendaAtual >= MAX_VENDAS) {
        return -1; // Limite de vendas atingido
    }

    Venda novaVenda(proximoNumeroFatura, idCliente);
    vendas.push_back(novaVenda);
    indiceVendaAtual++;

    return proximoNumeroFatura++;
}

// Adiciona um item a uma venda existente
bool Loja::adicionarItemVenda(int numeroFatura, int idProduto, int quantidade) {
    Venda* venda = buscarVenda(numeroFatura);
    Produto* produto = buscarProduto(idProduto);

    if (!venda || !produto) {
        return false;
    }

    if (!produto->temEstoqueSuficiente(quantidade)) {
        return false;
    }

    // Remove do estoque
    if (!produto->removerEstoque(quantidade)) {
        return false;
    }

    // Adiciona à venda
    venda->adicionarItem(idProduto, produto->getNome(), quantidade, produto->getPrecoCusto());

    return true;
}

// Finaliza uma venda processando o pagamento
bool Loja::finalizarVenda(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) {
        return false;
    }

    // Exibe o checkout e pede confirmação
    if (!venda->exibirCheckout()) {
        return false; // Cliente desistiu da compra
    }

    // Verifica se a venda foi sorteada como grátis
    if (venda->verificarVendaGratis()) {
        venda->processarPagamento(0.0f);
        cout << "\n*** PARABÉNS! Esta venda foi sorteada como GRÁTIS! ***\n";
    } else {
        if (valorEntregue < venda->getTotalComIVA()) {
            return false;
        }
        venda->processarPagamento(valorEntregue);
    }

    return true;
}

// Finaliza uma venda silenciosamente (para vendas iniciais)
bool Loja::finalizarVendaSilenciosa(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) {
        return false;
    }

    // Não exibe checkout, apenas processa o pagamento
    if (valorEntregue < venda->getTotalComIVA()) {
        return false;
    }
    
    venda->processarPagamento(valorEntregue);
    return true;
}

// Gera relatório do estoque atual
void Loja::relatorioStock() const {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                RELATÓRIO DE STOCK                                   ║\n";
    cout << "╠══════╦══════════════════════════════════╦═══════╦═══════════════╦═══════════════════╣\n";
    cout << "║  ID  ║           PRODUTO                ║  QTD  ║  PREÇO UNIT.  ║   VALOR TOTAL     ║\n";
    cout << "╠══════╬══════════════════════════════════╬═══════╬═══════════════╬═══════════════════╣\n";
    
    float valorTotalStock = 0.0f;
    int quantidadeTotalItens = 0;

    for (const auto& produto : produtos) {
        float valorProduto = produto.getPrecoCusto() * produto.getQuantidade();
        valorTotalStock += valorProduto;
        quantidadeTotalItens += produto.getQuantidade();

        string nomeTruncado = produto.getNome();
        string status = "";
        
        // Adiciona indicador de status
        if (produto.getQuantidade() == 0) {
            status = " [SEM]";
            if (nomeTruncado.length() > 27) {
                nomeTruncado = nomeTruncado.substr(0, 27);
            }
        } else if (produto.getQuantidade() <= 5) {
            status = " [BAIXO]";
            if (nomeTruncado.length() > 25) {
                nomeTruncado = nomeTruncado.substr(0, 25);
            }
        } else {
            if (nomeTruncado.length() > 32) {
                nomeTruncado = nomeTruncado.substr(0, 29) + "...";
            }
        }

        cout << "║ " << right << setw(4) << produto.getId() << " ║ "
             << left << setw(32) << (nomeTruncado + status) << " ║ "
             << right << setw(5) << produto.getQuantidade() << " ║ "
             << right << setw(12) << fixed << setprecision(2) << produto.getPrecoCusto() << "€ ║ "
             << right << setw(16) << fixed << setprecision(2) << valorProduto << "€ ║\n";
    }

    cout << "╠══════╬══════════════════════════════════╬═══════╬═══════════════╬═══════════════════╣\n";
    cout << "║      ║ TOTAL GERAL                      ║ " << right << setw(5) << quantidadeTotalItens << " ║               ║ "
         << right << setw(16) << fixed << setprecision(2) << valorTotalStock << "€ ║\n";
    cout << "╚══════╩══════════════════════════════════╩═══════╩═══════════════╩═══════════════════╝\n";
    cout << "\n";
    cout << "Legenda: [BAIXO] = Stock baixo (<=5)  [SEM] = Sem stock\n";
    cout << "\n";
}

// Gera relatório de vendas por produto
void Loja::relatorioVendasPorProduto(int idProduto) const {
    const Produto* produto = buscarProduto(idProduto);
    if (!produto) {
        cout << "Produto com ID " << idProduto << " não encontrado!\n";
        return;
    }

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                           RELATÓRIO DE VENDAS POR PRODUTO                           ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << "Produto: " << produto->getNome() << " (ID: " << idProduto << ")\n";
    cout << "Preço de Custo: " << fixed << setprecision(2) << produto->getPrecoCusto() << "€\n";
    cout << "Preço de Venda: " << fixed << setprecision(2) << produto->getPrecoVenda() << "€\n";
    cout << "\n";

    cout << "╔═══════════╦════════════════════╦═══════════╦═══════════════╦═══════════════════╗\n";
    cout << "║  FATURA   ║       DATA         ║ CLIENTE   ║   QUANTIDADE  ║   VALOR TOTAL     ║\n";
    cout << "╠═══════════╬════════════════════╬═══════════╬═══════════════╬═══════════════════╣\n";

    int totalQuantidadeVendida = 0;
    float totalValorVendido = 0.0f;
    bool encontrouVendas = false;

    for (const auto& venda : vendas) {
        for (int i = 0; i < venda.getNumItens(); i++) {
            const ItemVenda* item = venda.getItem(i);
            if (item && item->idProduto == idProduto) {
                encontrouVendas = true;
                totalQuantidadeVendida += item->quantidade;
                totalValorVendido += item->total;

                cout << "║ " << right << setw(9) << venda.getNumeroFatura() << " ║ "
                     << left << setw(18) << venda.getData() << " ║ "
                     << right << setw(9) << venda.getNumeroCliente() << " ║ "
                     << right << setw(13) << item->quantidade << " ║ "
                     << right << setw(16) << fixed << setprecision(2) << item->total << "€ ║\n";
            }
        }
    }

    if (!encontrouVendas) {
        cout << "║                           Nenhuma venda encontrada para este produto                ║\n";
    } else {
        cout << "╠═══════════╬════════════════════╬═══════════╬═══════════════╬═══════════════════╣\n";
        cout << "║   TOTAL   ║                    ║           ║ " << right << setw(13) << totalQuantidadeVendida << " ║ "
             << right << setw(16) << fixed << setprecision(2) << totalValorVendido << "€ ║\n";
    }

    cout << "╚═══════════╩════════════════════╩═══════════╩═══════════════╩═══════════════════╝\n";
    cout << "\n";
}

// Gera relatório total de vendas
void Loja::relatorioTotalVendas() const {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                              RELATÓRIO TOTAL DE VENDAS                              ║\n";
    cout << "╠═══════════╦════════════════════╦═══════════╦═══════════╦═══════════════════════════╣\n";
    cout << "║  FATURA   ║       DATA         ║ CLIENTE   ║   ITENS   ║       VALOR TOTAL         ║\n";
    cout << "╠═══════════╬════════════════════╬═══════════╬═══════════╬═══════════════════════════╣\n";

    float valorTotalGeral = 0.0f;
    int totalVendas = 0;

    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            totalVendas++;
            valorTotalGeral += venda.getTotalComIVA();

            cout << "║ " << right << setw(9) << venda.getNumeroFatura() << " ║ "
                 << left << setw(18) << venda.getData() << " ║ "
                 << right << setw(9) << venda.getNumeroCliente() << " ║ "
                 << right << setw(9) << venda.getNumItens() << " ║ "
                 << right << setw(24) << fixed << setprecision(2) << venda.getTotalComIVA() << "€ ║\n";
        }
    }

    if (totalVendas == 0) {
        cout << "║                              Nenhuma venda registrada                               ║\n";
    } else {
        cout << "╠═══════════╬════════════════════╬═══════════╬═══════════╬═══════════════════════════╣\n";
        cout << "║   TOTAL   ║ " << totalVendas << " vendas realizadas ║           ║           ║ "
             << right << setw(24) << fixed << setprecision(2) << valorTotalGeral << "€ ║\n";
    }

    cout << "╚═══════════╩════════════════════╩═══════════╩═══════════╩═══════════════════════════╝\n";
    cout << "\n";
}

// Inicializa a loja com dados de exemplo
void Loja::inicializarDadosIniciais() {
    // Adicionar clientes iniciais
    adicionarCliente("João Silva", "912345678", "Rua das Flores, 123, Lisboa");
    adicionarCliente("Maria Santos", "923456789", "Av. da Liberdade, 456, Porto");
    adicionarCliente("Pedro Costa", "934567890", "Rua do Comércio, 789, Coimbra");
    adicionarCliente("Ana Rodrigues", "945678901", "Praça da República, 321, Braga");
    adicionarCliente("Carlos Mendes", "956789012", "Rua Central, 654, Faro");
    adicionarCliente("Sofia Pereira", "967890123", "Av. dos Aliados, 987, Aveiro");
    adicionarCliente("Miguel Ferreira", "978901234", "Rua da Paz, 147, Viseu");
    adicionarCliente("Catarina Lopes", "989012345", "Largo do Município, 258, Évora");

    // Adicionar produtos iniciais
    adicionarProduto("Placa Mãe ASUS B450", 15, 89.99f);
    adicionarProduto("Processador AMD Ryzen 5", 12, 199.99f);
    adicionarProduto("Memória RAM 16GB DDR4", 25, 79.99f);
    adicionarProduto("Disco SSD 1TB NVMe", 20, 87.94f);
    adicionarProduto("Placa Gráfica RTX 3060", 8, 399.99f);
    adicionarProduto("Fonte 650W 80+ Bronze", 18, 71.95f);
    adicionarProduto("Caixa ATX Mid Tower", 10, 59.99f);
    adicionarProduto("Monitor 24'' Full HD", 14, 143.91f);
    adicionarProduto("Teclado Mecânico RGB", 22, 89.99f);
    adicionarProduto("Cooler CPU", 30, 29.99f);

    // Criar algumas vendas de exemplo
    criarVendasIniciais();
}

// Função auxiliar para criar vendas iniciais
void Loja::criarVendasIniciais() {
    // Venda 1: João Silva
    int venda1 = criarVenda(1);
    adicionarItemVenda(venda1, 1, 1); // Placa Mãe
    adicionarItemVenda(venda1, 2, 1); // Processador
    adicionarItemVenda(venda1, 3, 2); // 2x RAM
    finalizarVendaSilenciosa(venda1, 500.0f);

    // Venda 2: Maria Santos
    int venda2 = criarVenda(2);
    adicionarItemVenda(venda2, 8, 1); // Monitor
    adicionarItemVenda(venda2, 7, 1); // Caixa
    finalizarVendaSilenciosa(venda2, 300.0f);

    // Venda 3: Pedro Costa
    int venda3 = criarVenda(3);
    adicionarItemVenda(venda3, 4, 2); // 2x SSD
    adicionarItemVenda(venda3, 6, 1); // Fonte
    finalizarVendaSilenciosa(venda3, 350.0f);

    // Venda 4: Ana Rodrigues
    int venda4 = criarVenda(4);
    adicionarItemVenda(venda4, 5, 1); // Placa Gráfica
    finalizarVendaSilenciosa(venda4, 600.0f);

    // Venda 5: Carlos Mendes
    int venda5 = criarVenda(5);
    adicionarItemVenda(venda5, 7, 1); // Caixa
    adicionarItemVenda(venda5, 10, 2); // 2x Cooler
    finalizarVendaSilenciosa(venda5, 150.0f);
}

