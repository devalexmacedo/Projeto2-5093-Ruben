#define _CRT_SECURE_NO_WARNINGS
#include "Loja.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

// Construtor
Loja::Loja() {
    proximoIdCliente = 1;
    proximoIdProduto = 1;
    proximoNumeroFatura = 1;
    indiceVendaAtual = 0;
    
    // Inicializar com dados pré-definidos
    inicializarDadosIniciais();
}

// Métodos para gestão de clientes
int Loja::adicionarCliente(const std::string& nome, const std::string& telefone, const std::string& morada) {
    Cliente novoCliente(nome, telefone, morada);
    novoCliente.setId(proximoIdCliente);
    clientes.push_back(novoCliente);
    return proximoIdCliente++;
}

bool Loja::removerCliente(int id) {
    auto it = std::find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });
    
    if (it != clientes.end()) {
        clientes.erase(it);
        return true;
    }
    return false;
}

bool Loja::alterarNomeCliente(int id, const std::string& novoNome) {
    Cliente* cliente = buscarCliente(id);
    if (cliente) {
        cliente->setNome(novoNome);
        return true;
    }
    return false;
}

Cliente* Loja::buscarCliente(int id) {
    auto it = std::find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });
    
    return (it != clientes.end()) ? &(*it) : nullptr;
}

void Loja::listarClientes() const {
    std::cout << "\n=============== LISTA DE CLIENTES ===============\n";
    std::cout << std::left << std::setw(5) << "ID" << "| "
              << std::left << std::setw(25) << "Nome" << "| "
              << std::left << std::setw(15) << "Telefone" << "| "
              << std::left << std::setw(30) << "Morada" << std::endl;
    std::cout << "=================================================\n";
    
    if (clientes.empty()) {
        std::cout << "Nenhum cliente cadastrado.\n";
    } else {
        for (const auto& cliente : clientes) {
            std::cout << std::left << std::setw(5) << cliente.getId() << "| "
                      << std::left << std::setw(25) << cliente.getNome() << "| "
                      << std::left << std::setw(15) << cliente.getTelefone() << "| "
                      << std::left << std::setw(30) << cliente.getMorada() << std::endl;
        }
    }
    std::cout << "=================================================\n";
}

// Métodos para gestão de produtos
int Loja::adicionarProduto(const std::string& nome, int quantidade, float precoCusto) {
    Produto novoProduto(nome, quantidade, precoCusto);
    novoProduto.setId(proximoIdProduto);
    produtos.push_back(novoProduto);
    return proximoIdProduto++;
}

bool Loja::removerProduto(int id) {
    auto it = std::find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });
    
    if (it != produtos.end()) {
        produtos.erase(it);
        return true;
    }
    return false;
}

bool Loja::adicionarEstoqueProduto(int id, int quantidade) {
    Produto* produto = buscarProduto(id);
    if (produto && quantidade > 0) {
        produto->adicionarEstoque(quantidade);
        return true;
    }
    return false;
}

bool Loja::atualizarPrecoProduto(int id, float novoPrecoCusto) {
    Produto* produto = buscarProduto(id);
    if (produto && novoPrecoCusto > 0) {
        produto->setPrecoCusto(novoPrecoCusto);
        return true;
    }
    return false;
}

Produto* Loja::buscarProduto(int id) {
    auto it = std::find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });
    
    return (it != produtos.end()) ? &(*it) : nullptr;
}

void Loja::listarProdutos() const {
    std::cout << "\n=============== ESTOQUE ATUAL ===============\n";
    std::cout << std::left << std::setw(5) << "ID" << "| "
              << std::left << std::setw(30) << "Nome do Produto" << "| "
              << std::left << std::setw(6) << "Qtd." << "| "
              << std::right << std::setw(12) << "Custo (EUR)" << "| "
              << std::right << std::setw(12) << "Venda (EUR)" << std::endl;
    std::cout << "=============================================\n";
    
    if (produtos.empty()) {
        std::cout << "Nenhum produto cadastrado.\n";
    } else {
        bool temProdutoComEstoque = false;
        for (const auto& produto : produtos) {
            if (produto.getQuantidade() > 0) {
                std::cout << std::left << std::setw(5) << produto.getId() << "| "
                          << std::left << std::setw(30) << produto.getNome() << "| "
                          << std::left << std::setw(6) << produto.getQuantidade() << "| "
                          << std::right << std::setw(12) << std::fixed << std::setprecision(2) 
                          << produto.getPrecoCusto() << "| "
                          << std::right << std::setw(12) << std::fixed << std::setprecision(2) 
                          << produto.getPrecoVenda() << std::endl;
                temProdutoComEstoque = true;
            }
        }
        if (!temProdutoComEstoque) {
            std::cout << "Todos os produtos estão sem estoque.\n";
        }
    }
    std::cout << "=============================================\n";
}

// Métodos para gestão de vendas
int Loja::criarVenda(int idCliente) {
    Cliente* cliente = buscarCliente(idCliente);
    if (!cliente) {
        return -1; // Cliente não encontrado
    }
    
    Venda novaVenda(proximoNumeroFatura, idCliente);
    
    // Se já temos 100 vendas, sobrescrever a mais antiga
    if (vendas.size() >= MAX_VENDAS) {
        vendas[indiceVendaAtual] = novaVenda;
        indiceVendaAtual = (indiceVendaAtual + 1) % MAX_VENDAS;
    } else {
        vendas.push_back(novaVenda);
        if (vendas.size() == MAX_VENDAS) {
            indiceVendaAtual = 0; // Começar a sobrescrever do início
        }
    }
    
    return proximoNumeroFatura++;
}

bool Loja::adicionarItemVenda(int numeroFatura, int idProduto, int quantidade) {
    Venda* venda = buscarVenda(numeroFatura);
    Produto* produto = buscarProduto(idProduto);
    
    if (!venda || !produto) {
        return false;
    }
    
    if (!produto->temEstoqueSuficiente(quantidade)) {
        return false;
    }
    
    // Adicionar item à venda
    venda->adicionarItem(idProduto, produto->getNome(), quantidade, produto->getPrecoCusto());
    
    // Atualizar estoque
    produto->removerEstoque(quantidade);
    
    return true;
}

bool Loja::finalizarVenda(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) {
        return false;
    }
    
    // Verificar se é venda grátis (25% de chance)
    if (venda->verificarVendaGratis()) {
        venda->processarPagamento(0.0f); // Venda grátis
        std::cout << "\n*** PARABÉNS! Esta venda foi sorteada como GRÁTIS! ***\n";
    } else {
        if (valorEntregue < venda->getTotalComIVA()) {
            return false; // Valor insuficiente
        }
        venda->processarPagamento(valorEntregue);
    }
    
    return true;
}

Venda* Loja::buscarVenda(int numeroFatura) {
    auto it = std::find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });
    
    return (it != vendas.end()) ? &(*it) : nullptr;
}

// Métodos para relatórios
void Loja::relatorioStock() const {
    std::cout << "\n=============== RELATÓRIO DE STOCK ===============\n";
    float valorTotalStock = 0.0f;
    int quantidadeTotalItens = 0;
    
    std::cout << std::left << std::setw(5) << "ID" << "| "
              << std::left << std::setw(30) << "Nome do Produto" << "| "
              << std::left << std::setw(6) << "Qtd." << "| "
              << std::right << std::setw(12) << "Valor Total" << std::endl;
    std::cout << "==================================================\n";
    
    for (const auto& produto : produtos) {
        float valorProduto = produto.getPrecoCusto() * produto.getQuantidade();
        valorTotalStock += valorProduto;
        quantidadeTotalItens += produto.getQuantidade();
        
        std::cout << std::left << std::setw(5) << produto.getId() << "| "
                  << std::left << std::setw(30) << produto.getNome() << "| "
                  << std::left << std::setw(6) << produto.getQuantidade() << "| "
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2) 
                  << valorProduto << std::endl;
    }
    
    std::cout << "==================================================\n";
    std::cout << "Total de itens em stock: " << quantidadeTotalItens << std::endl;
    std::cout << "Valor total do stock: " << std::fixed << std::setprecision(2) 
              << valorTotalStock << " EUR" << std::endl;
    std::cout << "==================================================\n";
}

void Loja::relatorioVendasPorProduto(const std::string& nomeProduto) const {
    std::cout << "\n=============== RELATÓRIO DE VENDAS POR PRODUTO ===============\n";
    std::cout << "Produto: " << nomeProduto << std::endl;
    std::cout << "===============================================================\n";
    
    int quantidadeVendida = 0;
    float valorTotalVendido = 0.0f;
    int numeroVendas = 0;
    
    for (const auto& venda : vendas) {
        // Aqui precisaríamos de um método para acessar os itens da venda
        // Como a classe Venda não tem esse método público, vamos implementá-lo
        // Por enquanto, vamos mostrar a estrutura do relatório
    }
    
    std::cout << "Quantidade total vendida: " << quantidadeVendida << std::endl;
    std::cout << "Valor total vendido: " << std::fixed << std::setprecision(2) 
              << valorTotalVendido << " EUR" << std::endl;
    std::cout << "Número de vendas: " << numeroVendas << std::endl;
    std::cout << "===============================================================\n";
}

void Loja::relatorioTotalVendas() const {
    std::cout << "\n=============== RELATÓRIO TOTAL DE VENDAS ===============\n";
    
    if (vendas.empty()) {
        std::cout << "Nenhuma venda registrada.\n";
        std::cout << "========================================================\n";
        return;
    }
    
    // Aqui implementaríamos a lógica para:
    // - Produto mais vendido
    // - Produto menos vendido  
    // - Valor do lucro do produto mais vendido
    // - Cliente que mais comprou em valor
    
    std::cout << "Total de vendas registradas: " << vendas.size() << std::endl;
    std::cout << "========================================================\n";
}

// Métodos auxiliares
void Loja::inicializarDadosIniciais() {
    // Adicionar clientes iniciais
    adicionarCliente("João Silva", "912345678", "Rua das Flores, 123");
    adicionarCliente("Maria Santos", "923456789", "Avenida Central, 456");
    adicionarCliente("Pedro Costa", "934567890", "Praça da República, 789");
    
    // Adicionar produtos iniciais
    adicionarProduto("Placa Mãe Asus B550", 20, 85.00f);
    adicionarProduto("Processador Ryzen 5 5600X", 20, 140.00f);
    adicionarProduto("Memoria RAM 16GB DDR4", 20, 35.00f);
    adicionarProduto("Disco SSD 1TB NVMe", 20, 55.00f);
    adicionarProduto("Fonte 650W 80+ Bronze", 20, 45.00f);
    adicionarProduto("Placa Grafica RTX 3060", 20, 260.00f);
    adicionarProduto("Caixa Mid Tower", 20, 40.00f);
    adicionarProduto("Cooler CPU ARGB", 20, 25.00f);
    adicionarProduto("Monitor 24'' Full HD", 20, 90.00f);
    adicionarProduto("Suporte Monitor", 20, 8.00f);
}

