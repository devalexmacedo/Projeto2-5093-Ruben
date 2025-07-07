#ifndef LOJA_H
#define LOJA_H

#include <string>
#include <vector>
#include "Cliente.h"
#include "Produto.h"
#include "Venda.h"

class Loja {
private:
    std::vector<Cliente> clientes;
    std::vector<Produto> produtos;
    std::vector<Venda> vendas;

    int proximoIdCliente;
    int proximoIdProduto;
    int proximoNumeroFatura;
    int indiceVendaAtual;

    static const int MAX_VENDAS = 100;

public:
    Loja();

    // Versões não-const para modificação
    Cliente* buscarCliente(int id);
    Produto* buscarProduto(int id);
    Venda* buscarVenda(int numeroFatura);

    // Versões const para acesso somente leitura
    const Cliente* buscarCliente(int id) const;
    const Produto* buscarProduto(int id) const;
    const Venda* buscarVenda(int numeroFatura) const;

    void inicializarDadosIniciais();

    // Gestão de Clientes
    int adicionarCliente(const std::string& nome, const std::string& telefone, const std::string& morada, const std::string& cidade);
    bool removerCliente(int id);
    bool alterarNomeCliente(int id, const std::string& novoNome);
    void listarClientes() const;

    // Gestão de Produtos
    int adicionarNovoProduto(const std::string& nome, int quantidade, float precoCusto);
    bool atualizarProduto(const std::string& nome, int quantidadeAdicional, float novoPrecoCusto);
    Produto* buscarProdutoPorNome(const std::string& nome);
    bool removerProduto(int id);
    bool adicionarEstoque(int id, int quantidade);
    bool atualizarPrecoProduto(int id, float novoPrecoCusto);
    void listarProdutos() const;

    // Gestão de Vendas
    int criarVenda(int idCliente);
    bool adicionarItemVenda(int numeroFatura, int idProduto, int quantidade);
    bool finalizarVenda(int numeroFatura, float valorEntregue);
    bool finalizarVendaSilenciosa(int numeroFatura, float valorEntregue); // Para vendas iniciais

    // Relatórios
    void relatorioStock() const;
    void relatorioVendasPorProduto(int idProduto) const;
    void relatorioTotalVendas() const;
    void relatorioEstatisticasVendas() const; // Novo: produto mais/menos vendido, lucros, melhor cliente

private:
    // Função auxiliar para criar vendas iniciais
    void criarVendasIniciais();
};

#endif // LOJA_H



