// Arquivo de definição da classe Cliente
#pragma once  // Impede que o arquivo seja incluído mais de uma vez

#include <string>

using namespace std;

// Representa um cliente do sistema com seus dados básicos
class Cliente {
private:
    // Dados do cliente
    int id;          // Código único de identificação
    string nome;     // Nome completo
    string telefone; // Telefone para contato
    string morada;   // Endereço completo
    string cidade;   // Cidade de residência

public:
    // Construtor padrão - cria cliente vazio
    Cliente();

    // Construtor completo - já preenche todos os dados
    Cliente(const string& nome, const string& telefone, const string& morada, const string& cidade);

    // Getters (métodos de consulta)
    int getId() const;            // Retorna o ID
    string getNome() const;       // Retorna o nome
    string getTelefone() const;   // Retorna o telefone
    string getMorada() const;     // Retorna o endereço
    string getCidade() const;     // Retorna a cidade

    // Setters (métodos de modificação)
    void setId(int newId);                    // Altera o ID
    void setNome(const string& newNome);      // Altera o nome
    void setTelefone(const string& newTelefone);  // Altera o telefone
    void setMorada(const string& newMorada);  // Altera o endereço
    void setCidade(const string& newCidade);  // Altera a cidade
};