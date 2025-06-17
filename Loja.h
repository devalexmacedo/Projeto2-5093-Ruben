#ifndef LOJA_H
#define LOJA_H

#include <vector>
#include <string>
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
    static const int MAX_VENDAS = 100;
    int indiceVendaAtual; // Para controlar o índice circular das vendas

public:
    // Construtor
    Loja();
    
    // Métodos para gestão de clientes
    int adicionarCliente(const std::string& nome, const std::string& telefone, const std::string& morada);
    bool removerCliente(int id);
    bool alterarNomeCliente(int id, const std::string& novoNome);
    Cliente* buscarCliente(int id);
    void listarClientes() const;
    
    // Métodos para gestão de produtos
    int adicionarProduto(const std::string& nome, int quantidade, float precoCusto);
    bool removerProduto(int id);
    bool adicionarEstoqueProduto(int id, int quantidade);
    bool atualizarPrecoProduto(int id, float novoPrecoCusto);
    Produto* buscarProduto(int id);
    void listarProdutos() const;
    
    // Métodos para gestão de vendas
    int criarVenda(int idCliente);
    bool adicionarItemVenda(int numeroFatura, int idProduto, int quantidade);
    bool finalizarVenda(int numeroFatura, float valorEntregue);
    Venda* buscarVenda(int numeroFatura);
    
    // Métodos para relatórios
    void relatorioStock() const;
    void relatorioVendasPorProduto(const std::string& nomeProduto) const;
    void relatorioTotalVendas() const;
    
    // Métodos auxiliares
    void inicializarDadosIniciais();
    void exibirMenu();
    
    // Getters
    int getProximoIdCliente() const { return proximoIdCliente; }
    int getProximoIdProduto() const { return proximoIdProduto; }
    int getProximoNumeroFatura() const { return proximoNumeroFatura; }
};

#endif // LOJA_H

