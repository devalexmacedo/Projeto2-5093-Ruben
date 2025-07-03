#include "Cliente.h"

using namespace std;

// Construtor padrão
Cliente::Cliente() : id(0) {}

// Construtor com parâmetros
Cliente::Cliente(const string& nome, const string& telefone, const string& morada, const string& cidade)
    : nome(nome), telefone(telefone), morada(morada), cidade(cidade), id(0) {}

// Retorna o ID do cliente
int Cliente::getId() const {
    return id;
}

// Retorna o nome do cliente
string Cliente::getNome() const {
    return nome;
}

// Retorna o telefone do cliente
string Cliente::getTelefone() const {
    return telefone;
}

// Retorna a morada do cliente
string Cliente::getMorada() const {
    return morada;
}

// Retorna a cidade do cliente
string Cliente::getCidade() const {
    return cidade;
}

// Define o ID do cliente
void Cliente::setId(int newId) {
    id = newId;
}

// Define o nome do cliente
void Cliente::setNome(const string& newNome) {
    nome = newNome;
}

// Define o telefone do cliente
void Cliente::setTelefone(const string& newTelefone) {
    telefone = newTelefone;
}

// Define a morada do cliente
void Cliente::setMorada(const string& newMorada) {
    morada = newMorada;
}

// Define a cidade do cliente
void Cliente::setCidade(const string& newCidade) {
    cidade = newCidade;
}



