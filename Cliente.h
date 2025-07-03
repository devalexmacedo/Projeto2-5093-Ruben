#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

using namespace std;

class Cliente {
private:
    int id;
    string nome;
    string telefone;
    string morada;
    string cidade;

public:
    // Construtor padrão
    Cliente();

    // Construtor com parâmetros
    Cliente(const string& nome, const string& telefone, const string& morada, const string& cidade);

    // Métodos de acesso
    int getId() const;
    string getNome() const;
    string getTelefone() const;
    string getMorada() const;
    string getCidade() const;

    // Métodos de modificação
    void setId(int newId);
    void setNome(const string& newNome);
    void setTelefone(const string& newTelefone);
    void setMorada(const string& newMorada);
    void setCidade(const string& newCidade);
};

#endif // CLIENTE_H



