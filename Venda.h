#ifndef VENDA_H
#define VENDA_H

#include <string>
#include <vector>

using namespace std;

// Estrutura para armazenar os detalhes de cada item vendido
struct ItemVenda {
    int idProduto;
    string nomeProduto;
    int quantidade;
    float precoUnitario;
    float precoSemIVA;
    float iva;
    float total;
    
    // Construtor padrão para inicializar todas as variáveis
    ItemVenda() : idProduto(0), quantidade(0), precoUnitario(0.0f), 
                  precoSemIVA(0.0f), iva(0.0f), total(0.0f) {}
};

class Venda {
private:
    int numeroFatura;
    int numeroCliente;
    vector<ItemVenda> itens;
    float totalSemIVA;
    float totalIVA;
    float totalComIVA;
    float valorEntregue;
    float troco;
    string data;

public:
    Venda();
    Venda(int numeroFatura, int numeroCliente);

    // Métodos de acesso
    int getNumeroFatura() const;
    int getNumeroCliente() const;
    int getNumItens() const;
    size_t getNumItens_sizet() const; // Versão alternativa para compatibilidade
    float getTotalSemIVA() const;
    float getTotalIVA() const;
    float getTotalComIVA() const;
    float getValorEntregue() const;
    float getTroco() const;
    string getData() const;

    // Métodos de modificação
    void setNumeroFatura(int numeroFatura);
    void setNumeroCliente(int numeroCliente);
    void setData(const string& data);

    // Métodos de operação
    void adicionarItem(int idProduto, const string& nomeProduto, int quantidade, float precoCusto);
    void calcularTotal();
    void processarPagamento(float valorEntregue);
    void imprimirTalao() const;
    bool exibirCheckout() const;
    bool verificarVendaGratis() const;

    const ItemVenda* getItem(int index) const;
    const ItemVenda* getItem(size_t index) const; // Sobrecarga para compatibilidade
};

#endif // VENDA_H

