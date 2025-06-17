#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
private:
    int id;                 // ID único do cliente (gerenciado automaticamente)
    std::string nome;       // Nome do cliente
    std::string telefone;   // Número de telefone
    std::string morada;     // Endereço do cliente

public:
    // Construtor padrão
    Cliente();
    
    // Construtor com parâmetros (sem ID, que será gerenciado automaticamente)
    Cliente(const std::string& nome, const std::string& telefone, const std::string& morada);
    
    // Métodos de acesso (getters)
    int getId() const;
    std::string getNome() const;
    std::string getTelefone() const;
    std::string getMorada() const;
    
    // Métodos de modificação (setters)
    void setId(int id);  // Usado apenas internamente pela classe Loja
    void setNome(const std::string& nome);
    void setTelefone(const std::string& telefone);
    void setMorada(const std::string& morada);
};

#endif // CLIENTE_H
