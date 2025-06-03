#pragma once

class Cliente {
private:
    int id;                 // ID único do cliente
    char nome[50];          // Nome do cliente
    char telefone[20];      // Número de telefone
    char morada[100];       // Endereço do cliente

public:
    // Construtor padrão
    Cliente();

    // Construtor com parâmetros
    Cliente(int id, char* nome, char* telefone, char* morada);

    // Métodos de acesso (getters)
    int getId();
    char* getNome();
    char* getTelefone();
    char* getMorada();

    // Métodos de modificação (setters)
    void setId(int id);
    void setNome(char* nome);
    void setTelefone(char* telefone);
    void setMorada(char* morada);
};