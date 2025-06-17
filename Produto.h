#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

class Produto {
private:
    int id;                 // ID único do produto (gerenciado automaticamente)
    std::string nome;       // Nome do produto
    int quantidade;         // Quantidade em estoque
    float precoCusto;       // Preço de custo do produto

public:
    // Construtor padrão
    Produto();
    
    // Construtor com parâmetros (sem ID, que será gerenciado automaticamente)
    Produto(const std::string& nome, int quantidade, float precoCusto);
    
    // Métodos de acesso (getters)
    int getId() const;
    std::string getNome() const;
    int getQuantidade() const;
    float getPrecoCusto() const;
    float getPrecoVenda() const;  // Calcula o preço de venda (custo + 30%)
    
    // Métodos de modificação (setters)
    void setId(int id);  // Usado apenas internamente pela classe Loja
    void setNome(const std::string& nome);
    void setQuantidade(int quantidade);
    void setPrecoCusto(float precoCusto);
    
    // Métodos adicionais
    void adicionarEstoque(int quantidade);  // Adiciona quantidade ao estoque
    void removerEstoque(int quantidade);    // Remove quantidade do estoque
    bool temEstoqueSuficiente(int quantidade) const;  // Verifica se há estoque suficiente
};

#endif // PRODUTO_H
