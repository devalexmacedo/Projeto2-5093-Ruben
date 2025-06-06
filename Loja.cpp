// Loja.cpp - Implementação da classe Loja
#define _CRT_SECURE_NO_WARNINGS
#include "Loja.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>

using namespace std;

// Construtor
Loja::Loja() {
    numProdutos = 0;
    numClientes = 0;
    numVendas = 0;
    proximoIdProduto = 1;
    proximoIdCliente = 1;
    proximoNumeroFatura = 1001;

    // Inicializar a loja com dados predefinidos
    inicializarDadosPredefinidos();
}

// Métodos para gestão de produtos
void Loja::adicionarProduto(char* nome, int quantidade, double precoCusto) {
    if (numProdutos < 100) {
        // Criar produto com o construtor sem ID
        Produto novoProduto(nome, quantidade, precoCusto);
        // Definir o ID automaticamente
        novoProduto.setId(proximoIdProduto);
        produtos[numProdutos] = novoProduto;
        numProdutos++;
        proximoIdProduto++;
        cout << "Produto adicionado com sucesso!\n";
    }
    else {
        cout << "Erro: Limite de produtos atingido!\n";
    }
}

void Loja::atualizarEstoque(int idProduto, int quantidade) {
    Produto* produto = buscarProdutoPorId(idProduto);
    if (produto != nullptr) {
        produto->adicionarEstoque(quantidade);
        cout << "Estoque atualizado com sucesso!\n";
    }
    else {
        cout << "Erro: Produto não encontrado!\n";
    }
}

void Loja::eliminarProduto(int idProduto) {
    int indice = -1;

    // Encontrar o índice do produto
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].getId() == idProduto) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        // Mover todos os produtos uma posição para trás
        for (int i = indice; i < numProdutos - 1; i++) {
            produtos[i] = produtos[i + 1];
        }
        numProdutos--;
        cout << "Produto eliminado com sucesso!\n";
    }
    else {
        cout << "Erro: Produto não encontrado!\n";
    }
}

Produto* Loja::buscarProdutoPorId(int idProduto) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].getId() == idProduto) {
            return &produtos[i];
        }
    }
    return nullptr;
}

Produto* Loja::buscarProdutoPorNome(char* nome) {
    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].getNome(), nome) == 0) {
            return &produtos[i];
        }
    }
    return nullptr;
}

void Loja::listarProdutos() {
    cout << "------------------------------ ESTOQUE ATUAL ------------------------------" << endl;
    cout << left << setw(5) << "ID" << "| "
        << left << setw(30) << "Nome do Produto" << "| "
        << left << setw(6) << "Qtd." << "| "
        << right << setw(18) << "Preco Custo (EUR)" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    bool estoqueVazioOuZerado = true;
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].getQuantidade() > 0) {
            cout << left << setw(5) << produtos[i].getId() << "| "
                << left << setw(30) << produtos[i].getNome() << "| "
                << left << setw(6) << produtos[i].getQuantidade() << "| "
                << right << setw(15) << fixed << setprecision(2) << produtos[i].getPrecoCusto() << " EUR" << endl;
            estoqueVazioOuZerado = false;
        }
    }

    if (estoqueVazioOuZerado) {
        cout << "O estoque está vazio ou todos os produtos têm quantidade 0." << endl;
    }

    cout << "---------------------------------------------------------------------------" << endl;
}

// Métodos para gestão de clientes
void Loja::adicionarCliente(char* nome, char* telefone, char* morada) {
    if (numClientes < 100) {
        // Criar cliente com o construtor sem ID
        Cliente novoCliente(nome, telefone, morada);
        // Definir o ID automaticamente
        novoCliente.setId(proximoIdCliente);
        clientes[numClientes] = novoCliente;
        numClientes++;
        proximoIdCliente++;
        cout << "Cliente adicionado com sucesso!\n";
    }
    else {
        cout << "Erro: Limite de clientes atingido!\n";
    }
}

void Loja::eliminarCliente(int idCliente) {
    int indice = -1;

    // Encontrar o índice do cliente
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].getId() == idCliente) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        // Mover todos os clientes uma posição para trás
        for (int i = indice; i < numClientes - 1; i++) {
            clientes[i] = clientes[i + 1];
        }
        numClientes--;
        cout << "Cliente eliminado com sucesso!\n";
    }
    else {
        cout << "Erro: Cliente não encontrado!\n";
    }
}

void Loja::alterarNomeCliente(int idCliente, char* novoNome) {
    Cliente* cliente = buscarClientePorId(idCliente);
    if (cliente != nullptr) {
        cliente->setNome(novoNome);
        cout << "Nome do cliente alterado com sucesso!\n";
    }
    else {
        cout << "Erro: Cliente não encontrado!\n";
    }
}

Cliente* Loja::buscarClientePorId(int idCliente) {
    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].getId() == idCliente) {
            return &clientes[i];
        }
    }
    return nullptr;
}

void Loja::listarClientes() {
    cout << "\n=== Lista de Clientes ===\n";
    cout << "ID  | Nome                      | Telefone        | Morada\n";
    cout << "--------------------------------------------------------------------\n";

    for (int i = 0; i < numClientes; i++) {
        cout << clientes[i].getId() << "   | ";
        cout << clientes[i].getNome() << "                      | ";
        cout << clientes[i].getTelefone() << "     | ";
        cout << clientes[i].getMorada() << "\n";
    }

    cout << "--------------------------------------------------------------------\n";
}

// Métodos para vendas
void Loja::iniciarVenda(int idCliente) {
    // Verificar se o cliente existe
    Cliente* cliente = buscarClientePorId(idCliente);
    if (cliente == nullptr) {
        cout << "Erro: Cliente não encontrado!\n";
        return;
    }

    // Obter a data atual
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char data[20];
    strftime(data, sizeof(data), "%d/%m/%Y %H:%M", timeinfo);

    // Criar nova venda
    Venda novaVenda(proximoNumeroFatura, idCliente, data);

    // Adicionar a venda ao array (substituindo a mais antiga se necessário)
    int indice = numVendas % 100;  // Circular buffer
    vendas[indice] = novaVenda;

    if (numVendas < 100) {
        numVendas++;
    }

    cout << "Venda iniciada para o cliente " << cliente->getNome() << "!\n";
    cout << "Número da fatura: " << proximoNumeroFatura << "\n";

    // Incrementar o número da fatura para a próxima venda
    proximoNumeroFatura++;
}

void Loja::adicionarItemVenda(int idProduto, int quantidade) {
    // Verificar se há vendas
    if (numVendas == 0) {
        cout << "Erro: Nenhuma venda iniciada!\n";
        return;
    }

    // Obter a venda atual (a última iniciada)
    int indiceVendaAtual = (numVendas - 1) % 100;
    Venda* vendaAtual = &vendas[indiceVendaAtual];

    // Buscar o produto pelo nome
    Produto* produto = buscarProdutoPorId(idProduto);
    if (produto == nullptr) {
        cout << "Erro: Produto não encontrado!\n";
        return;
    }

    // Verificar se há estoque suficiente
    if (!produto->temEstoqueSuficiente(quantidade)) {
        cout << "Erro: Estoque insuficiente!\n";
        return;
    }

    // Adicionar o item à venda
    int linha = vendaAtual->getNumItens() + 1;
    vendaAtual->adicionarItem(linha, produto->getNome(), quantidade, produto->getPrecoVenda());

    // Atualizar o estoque
    produto->removerEstoque(quantidade);

    cout << "Item adicionado à venda: " << quantidade << "x " << produto->getNome() << "\n";
}

// Nova função de checkout
bool Loja::checkoutVenda() {
    // Verificar se há vendas
    if (numVendas == 0) {
        cout << "Erro: Nenhuma venda iniciada!\n";
        return false;
    }

    // Obter a venda atual (a última iniciada)
    int indiceVendaAtual = (numVendas - 1) % 100;
    Venda* vendaAtual = &vendas[indiceVendaAtual];

    // Chamar o método checkout da venda
    return vendaAtual->checkout();
}

void Loja::finalizarVenda(double valorEntregue) {
    // Verificar se há vendas
    if (numVendas == 0) {
        cout << "Erro: Nenhuma venda iniciada!\n";
        return;
    }

    // Obter a venda atual (a última iniciada)
    int indiceVendaAtual = (numVendas - 1) % 100;
    Venda* vendaAtual = &vendas[indiceVendaAtual];

    // Verificar se o valor entregue é suficiente
    if (valorEntregue < vendaAtual->getTotalComIVA()) {
        cout << "Erro: Valor entregue insuficiente!\n";
        return;
    }

    // Processar o pagamento
    vendaAtual->processarPagamento(valorEntregue);

    // Imprimir o talão
    vendaAtual->imprimirTalao();

    cout << "Venda finalizada com sucesso!\n";
}

// Métodos para relatórios
void Loja::relatorioEstoque() {
    cout << "\n=== Relatório de Estoque ===\n";
    cout << "ID  | Nome                      | Quantidade | Preço Custo | Preço Venda\n";
    cout << "--------------------------------------------------------------------\n";

    int totalItens = 0;
    double valorTotalCusto = 0.0;
    double valorTotalVenda = 0.0;

    for (int i = 0; i < numProdutos; i++) {
        cout << produtos[i].getId() << "   | ";
        cout << produtos[i].getNome() << "                      | ";
        cout << produtos[i].getQuantidade() << "         | ";
        cout << produtos[i].getPrecoCusto() << " €       | ";
        cout << produtos[i].getPrecoVenda() << " €\n";

        totalItens += produtos[i].getQuantidade();
        valorTotalCusto += produtos[i].getPrecoCusto() * produtos[i].getQuantidade();
        valorTotalVenda += produtos[i].getPrecoVenda() * produtos[i].getQuantidade();
    }

    cout << "--------------------------------------------------------------------\n";
    cout << "Total de itens em estoque: " << totalItens << "\n";
    cout << "Valor total de custo: " << valorTotalCusto << " €\n";
    cout << "Valor total de venda: " << valorTotalVenda << " €\n";
    cout << "Lucro potencial: " << valorTotalVenda - valorTotalCusto << " €\n";
}

void Loja::relatorioVendasPorProduto(char* nomeProduto) {
    cout << "\n=== Relatório de Vendas do Produto: " << nomeProduto << " ===\n";
    cout << "Fatura | Data                | Quantidade | Valor\n";
    cout << "----------------------------------------------------\n";

    int totalQuantidade = 0;
    double totalValor = 0.0;

    for (int i = 0; i < numVendas; i++) {
        for (int j = 0; j < vendas[i].getNumItens(); j++) {
            if (strcmp(vendas[i].getNomeProduto(j), nomeProduto) == 0) {
                cout << vendas[i].getNumeroFatura() << "    | ";
                cout << vendas[i].getData() << " | ";
                cout << vendas[i].getQuantidade(j) << "         | ";
                double valor = (vendas[i].getPrecoSemIVA(j) + vendas[i].getIVA(j)) * vendas[i].getQuantidade(j);
                cout << valor << " €\n";

                totalQuantidade += vendas[i].getQuantidade(j);
                totalValor += valor;
            }
        }
    }

    cout << "----------------------------------------------------\n";
    cout << "Total vendido: " << totalQuantidade << " unidades\n";
    cout << "Valor total: " << totalValor << " €\n";
}

void Loja::relatorioTotalVendas() {
    cout << "\n=== Relatório Total de Vendas ===\n";

    // Arrays para contar vendas por produto
    char produtosVendidos[100][50];
    int quantidadesPorProduto[100];
    double valoresPorProduto[100];
    int numProdutosVendidos = 0;

    // Arrays para contar compras por cliente
    int clientesCompradores[100];
    double valoresPorCliente[100];
    int numClientesCompradores = 0;

    // Calcular totais
    double totalVendas = 0.0;

    // Processar todas as vendas
    for (int i = 0; i < numVendas; i++) {
        int idCliente = vendas[i].getNumeroCliente();
        double valorVenda = vendas[i].getTotalComIVA();
        totalVendas += valorVenda;

        // Adicionar cliente à lista ou atualizar valor
        bool clienteEncontrado = false;
        for (int j = 0; j < numClientesCompradores; j++) {
            if (clientesCompradores[j] == idCliente) {
                valoresPorCliente[j] += valorVenda;
                clienteEncontrado = true;
                break;
            }
        }

        if (!clienteEncontrado && numClientesCompradores < 100) {
            clientesCompradores[numClientesCompradores] = idCliente;
            valoresPorCliente[numClientesCompradores] = valorVenda;
            numClientesCompradores++;
        }

        // Processar itens da venda
        for (int j = 0; j < vendas[i].getNumItens(); j++) {
            char* nomeProduto = vendas[i].getNomeProduto(j);
            int quantidade = vendas[i].getQuantidade(j);
            double valor = (vendas[i].getPrecoSemIVA(j) + vendas[i].getIVA(j)) * quantidade;

            // Adicionar produto à lista ou atualizar quantidade e valor
            bool produtoEncontrado = false;
            for (int k = 0; k < numProdutosVendidos; k++) {
                if (strcmp(produtosVendidos[k], nomeProduto) == 0) {
                    quantidadesPorProduto[k] += quantidade;
                    valoresPorProduto[k] += valor;
                    produtoEncontrado = true;
                    break;
                }
            }

            if (!produtoEncontrado && numProdutosVendidos < 100) {
                strcpy(produtosVendidos[numProdutosVendidos], nomeProduto);
                quantidadesPorProduto[numProdutosVendidos] = quantidade;
                valoresPorProduto[numProdutosVendidos] = valor;
                numProdutosVendidos++;
            }
        }
    }

    // Encontrar produto mais vendido e menos vendido
    int indiceMaisVendido = -1;
    int indiceMenosVendido = -1;
    int maxQuantidade = -1;
    int minQuantidade = 999999;

    for (int i = 0; i < numProdutosVendidos; i++) {
        if (quantidadesPorProduto[i] > maxQuantidade) {
            maxQuantidade = quantidadesPorProduto[i];
            indiceMaisVendido = i;
        }

        if (quantidadesPorProduto[i] < minQuantidade) {
            minQuantidade = quantidadesPorProduto[i];
            indiceMenosVendido = i;
        }
    }

    // Encontrar cliente que mais comprou em valor
    int indiceClienteMaisComprou = -1;
    double maxValorCliente = -1.0;

    for (int i = 0; i < numClientesCompradores; i++) {
        if (valoresPorCliente[i] > maxValorCliente) {
            maxValorCliente = valoresPorCliente[i];
            indiceClienteMaisComprou = i;
        }
    }

    // Exibir resultados
    cout << "Total de vendas: " << totalVendas << " €\n";

    if (indiceMaisVendido != -1) {
        cout << "Produto mais vendido: " << produtosVendidos[indiceMaisVendido]
            << " (" << quantidadesPorProduto[indiceMaisVendido] << " unidades)\n";

            // Calcular lucro do produto mais vendido
            Produto* produto = buscarProdutoPorNome(produtosVendidos[indiceMaisVendido]);
            if (produto != nullptr) {
                double precoCusto = produto->getPrecoCusto();
                double precoVenda = produto->getPrecoVenda();
                double lucroUnitario = precoVenda - precoCusto;
                double lucroTotal = lucroUnitario * quantidadesPorProduto[indiceMaisVendido];

                cout << "Lucro do produto mais vendido: " << lucroTotal << " €\n";
            }
    }

    if (indiceMenosVendido != -1) {
        cout << "Produto menos vendido: " << produtosVendidos[indiceMenosVendido]
            << " (" << quantidadesPorProduto[indiceMenosVendido] << " unidades)\n";
    }

    if (indiceClienteMaisComprou != -1) {
        Cliente* cliente = buscarClientePorId(clientesCompradores[indiceClienteMaisComprou]);
        if (cliente != nullptr) {
            cout << "Cliente que mais comprou em valor: " << cliente->getNome()
                << " (" << valoresPorCliente[indiceClienteMaisComprou] << " €)\n";
        }
    }
}

// Método para inicializar a loja com dados predefinidos
void Loja::inicializarDadosPredefinidos() {
    // Adicionar alguns produtos
    adicionarProduto((char*)"Arroz 1kg", 50, 1.20);
    adicionarProduto((char*)"Feijão 1kg", 40, 2.30);
    adicionarProduto((char*)"Açúcar 1kg", 60, 0.90);
    adicionarProduto((char*)"Café 250g", 30, 3.50);
    adicionarProduto((char*)"Leite 1L", 100, 0.70);
    adicionarProduto((char*)"Óleo 1L", 45, 1.80);
    adicionarProduto((char*)"Sal 1kg", 70, 0.50);
    adicionarProduto((char*)"Macarrão 500g", 55, 1.10);
    adicionarProduto((char*)"Farinha 1kg", 40, 0.85);
    adicionarProduto((char*)"Biscoito 200g", 65, 1.40);

    // Adicionar alguns clientes
    adicionarCliente((char*)"João Silva", (char*)"912345678", (char*)"Rua A, 123");
    adicionarCliente((char*)"Maria Santos", (char*)"923456789", (char*)"Rua B, 456");
    adicionarCliente((char*)"Pedro Oliveira", (char*)"934567890", (char*)"Rua C, 789");
    adicionarCliente((char*)"Ana Pereira", (char*)"945678901", (char*)"Rua D, 012");
    adicionarCliente((char*)"Carlos Ferreira", (char*)"956789012", (char*)"Rua E, 345");
}

