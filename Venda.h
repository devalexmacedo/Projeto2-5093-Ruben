#ifndef VENDA_H
#define VENDA_H

#include <string>
#include <vector>
#include "Produto.h"

// Estrutura para armazenar os itens da venda
struct ItemVenda {
    int idProduto;
    std::string nomeProduto;
    int quantidade;
    float precoUnitario;
    float precoSemIVA;
    float iva;
    float total;
};

class Venda {
private:
    int numeroFatura;           // Número único da fatura
    int numeroCliente;          // ID do cliente que realizou a compra
    std::vector<ItemVenda> itens; // Itens da venda
    float totalSemIVA;          // Total sem IVA
    float totalIVA;             // Total de IVA
    float totalComIVA;          // Total com IVA
    float valorEntregue;        // Valor pago pelo cliente
    float troco;                // Troco a devolver
    std::string data;           // Data da venda

public:
    // Construtor padrão
    Venda();
    
    // Construtor com parâmetros básicos
    Venda(int numeroFatura, int numeroCliente);
    
    // Métodos de acesso (getters)
    int getNumeroFatura() const;
    int getNumeroCliente() const;
    int getNumItens() const;
    float getTotalSemIVA() const;
    float getTotalIVA() const;
    float getTotalComIVA() const;
    float getValorEntregue() const;
    float getTroco() const;
    std::string getData() const;
    
    // Métodos de modificação (setters)
    void setNumeroFatura(int numeroFatura);
    void setNumeroCliente(int numeroCliente);
    void setData(const std::string& data);
    
    // Métodos adicionais
    void adicionarItem(int idProduto, const std::string& nomeProduto, int quantidade, float precoCusto);
    void calcularTotal();
    void processarPagamento(float valorEntregue);
    void imprimirTalao() const; // Método para imprimir o talão com fundo branco e letra preta
    
    // Método para verificar se a venda foi sorteada como grátis (25% de chance)
    bool verificarVendaGratis() const;
};

#endif // VENDA_H
