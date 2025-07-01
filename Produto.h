#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

using namespace std;

class Produto {
private:
    int id;
    string nome;
    int quantidade;
    float precoCusto;
    float precoVenda;

    // Calcula o preço de venda com base no custo
    void calcularPrecoVenda();

public:
    // Construtor padrão
    Produto();

    // Construtor com parâmetros
    Produto(const string& nome, int quantidade, float precoCusto);

    // Métodos de acesso
    int getId() const;
    string getNome() const;
    int getQuantidade() const;
    float getPrecoCusto() const;
    float getPrecoVenda() const;

    // Métodos de modificação
    void setId(int newId);
    void setNome(const string& newNome);
    void setPrecoCusto(float newPrecoCusto);

    // Métodos de gestão de estoque
    void adicionarEstoque(int qtd);
    bool removerEstoque(int qtd);
    bool temEstoqueSuficiente(int qtd) const;
};

#endif // PRODUTO_H

