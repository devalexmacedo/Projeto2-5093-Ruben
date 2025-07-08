#include "Cliente.h" // Inclui o cabeçalho da classe Cliente

using namespace std; // Usa o namespace padrão para facilitar o acesso a string, vector, etc.

// Construtor padrão da classe Cliente.
Cliente::Cliente() : id() {}

// Construtor com parâmetros da classe Cliente.
Cliente::Cliente(const string& nome, const string& telefone, const string& morada, const string& cidade)
    : nome(nome), telefone(telefone), morada(morada), cidade(cidade), id(0) {
}

// Método de acesso (getter) para o ID do cliente.
int Cliente::getId() const {
    return id;
}

// Método de acesso (getter) para o nome do cliente.
string Cliente::getNome() const {
    return nome;
}

// Método de acesso (getter) para o telefone do cliente.
string Cliente::getTelefone() const {
    return telefone;
}

// Método de acesso (getter) para a morada (endereço) do cliente.
string Cliente::getMorada() const {
    return morada;
}

// Método de acesso (getter) para a cidade do cliente.
string Cliente::getCidade() const {
    return cidade;
}

// Método de modificação (setter) para o ID do cliente.
void Cliente::setId(int newId) {
    id = newId;
}

// Método de modificação (setter) para o nome do cliente.
void Cliente::setNome(const string& newNome) {
    nome = newNome;
}

// Método de modificação (setter) para o telefone do cliente.
void Cliente::setTelefone(const string& newTelefone) {
    telefone = newTelefone;
}

// Método de modificação (setter) para a morada do cliente.
void Cliente::setMorada(const string& newMorada) {
    morada = newMorada;
}

// Método de modificação (setter) para a cidade do cliente.
void Cliente::setCidade(const string& newCidade) {
    cidade = newCidade;
}
