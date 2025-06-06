// Cliente.h - Definição da classe Cliente
#pragma once

class Cliente {
private:
    int id;                 // ID único do cliente (gerenciado pela classe Loja)
    char nome[50];          // Nome do cliente
    char telefone[20];      // Número de telefone
    char morada[100];       // Endereço do cliente

public:
    // Construtor padrão
    Cliente();

    // Construtor com parâmetros (sem ID, que será gerenciado pela classe Loja)
    Cliente(char* nome, char* telefone, char* morada);

    // Métodos de acesso (getters)
    int getId();
    char* getNome();
    char* getTelefone();
    char* getMorada();

    // Métodos de modificação (setters)
    void setId(int id);  // Usado apenas internamente pela classe Loja
    void setNome(char* nome);
    void setTelefone(char* telefone);
    void setMorada(char* morada);
};
