#pragma once  // Previne inclusões múltiplas

#include "Cliente.h"
#include "Produto.h"
#include "Venda.h"
#include <vector>
#include <string>
#include <deque>

using namespace std;

//Limitar a 100 vendas e usar o FIFO;
constexpr size_t LIMITE_VENDAS = 100;

// Classe principal que gerencia toda a operação da loja
class Loja {
private:
    // Dados armazenados
    vector<Cliente> clientes;      // Cadastro de clientes
    vector<Produto> produtos;      // Catálogo de produtos
    deque<Venda> vendas;        // Histórico de vendas

    // Contadores para IDs
    int proximoIdCliente = 1;           // Próximo ID para novo cliente
    int proximoIdProduto = 1;           // Próximo ID para novo produto
    int proximoNumeroFatura = 1;        // Número da próxima fatura

public:
    // Inicialização
    Loja();  // Construtor padrão

    // === Gestão de Clientes ===
    int adicionarCliente(const std::string& nome, const std::string& telefone,
        const string& morada, const string& cidade);
    bool removerCliente(int id);
    bool alterarNomeCliente(int id, const string& novoNome);
    void listarClientes() const;

    // === Gestão de Produtos ===
    int adicionarNovoProduto(const string& nome, int quantidade, float precoCusto);
    bool atualizarProduto(const string& nome, int quantidadeAdicional, float novoPrecoCusto);
    bool removerProduto(int id);
    bool adicionarEstoque(int id, int quantidade);
    bool atualizarPrecoProduto(int id, float novoPrecoCusto);
    void listarProdutos() const;
    void relatorioStock() const;

    // === Processamento de Vendas ===
    int criarVenda(int idCliente);
    bool adicionarItemVenda(int numeroFatura, int idProduto, int quantidade);
    bool finalizarVenda(int numeroFatura, float valorEntregue);
    bool finalizarVendaSilenciosa(int numeroFatura, float valorEntregue); // Para testes

    // === Relatórios ===
    void relatorioVendasPorProduto(int idProduto) const;
    void relatorioTotalVendas() const;
    void relatorioEstatisticasVendas() const;

    // === Buscas ===
    // Versões const (para consulta) e não-const (para modificação)
    const Cliente* buscarCliente(int id) const;
    Cliente* buscarCliente(int id);
    const Produto* buscarProduto(int id) const;
    Produto* buscarProduto(int id);
    const Venda* buscarVenda(int numeroFatura) const;
    Venda* buscarVenda(int numeroFatura);
    Produto* buscarProdutoPorNome(const string& nome);

    // === Inicialização ===
    void inicializarDadosIniciais();  // Carrega dados de exemplo

private:
    // Métodos internos
    void criarVendasIniciais();  // Popula vendas iniciais para demonstração
};