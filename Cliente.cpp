#include "Cliente.h"

// Construtor padrão
Cliente::Cliente() : id(0) {}

// Construtor com parâmetros
Cliente::Cliente(const string& nome, const string& telefone, const string& morada)
    : nome(nome), telefone(telefone), morada(morada), id(0) {}

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

// Define o ID do cliente
void Cliente::setId(int newId) {
    id = newId;
}

void Cliente::setNome(const std::string& nome) {
    this->nome = nome;
}

void Cliente::setTelefone(const std::string& telefone) {
    this->telefone = telefone;
}

void Cliente::setMorada(const std::string& morada) {
    this->morada = morada;
}

