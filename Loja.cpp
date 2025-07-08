#define _CRT_SECURE_NO_WARNINGS
#include "Loja.h"
#include "utilitario.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

// Construtor da classe Loja
Loja::Loja() : proximoIdCliente(1), proximoIdProduto(1), proximoNumeroFatura(1000) {
}


// Remove um cliente pelo ID
bool Loja::removerCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });

    if (it != clientes.end()) {
        clientes.erase(it);
        return true;
    }
    return false;
}

// Altera o nome de um cliente
bool Loja::alterarNomeCliente(int id, const string& novoNome) {
    Cliente* cliente = buscarCliente(id);
    if (cliente) {
        cliente->setNome(novoNome);
        return true;
    }
    return false;
}



// Lista todos os clientes cadastrados
void Loja::listarClientes() const {
    cout << "\n";
    cout << "+=========================================================================================================+\n";
    cout << "|                                           CLIENTES CADASTRADOS                                          |\n";
    cout << "+=========================================================================================================+\n";
    cout << "\n";

    if (clientes.empty()) {
        cout << "Nenhum cliente cadastrado.\n\n";
        return;
    }

    cout << "+====+===============================+=============+=================================+===================+\n";
    cout << "| ID |             NOME              |   TELEFONE  |             MORADA              |       CIDADE      |\n";
    cout << "+====+===============================+=============+=================================+===================+\n";

    for (const auto& cliente : clientes) {
        string nomeTruncado = cliente.getNome();
        if (nomeTruncado.length() > 30) {
            nomeTruncado = nomeTruncado.substr(0, 29) + "...";
        }

        string moradaTruncada = cliente.getMorada();
        if (moradaTruncada.length() > 30) {
            moradaTruncada = moradaTruncada.substr(0, 29) + "...";
        }

        string cidadeTruncada = cliente.getCidade();
        if (cidadeTruncada.length() > 17) {
            cidadeTruncada = cidadeTruncada.substr(0, 14) + "...";
        }

        cout << "| " << right << setw(2) << cliente.getId() << " | "
            << left << setw(29) << nomeTruncado << " | "
            << left << setw(11) << cliente.getTelefone() << " | "
            << left << setw(31) << moradaTruncada << " | "
            << left << setw(17) << cidadeTruncada << " |\n";
    }

    cout << "+====+===============================+=============+=================================+===================+\n";
    cout << "\n";
}

// Adiciona um novo produto
// Retorna o ID do novo produto, ou -1 se a quantidade/preço for inválida.
int Loja::adicionarNovoProduto(const string& nome, int quantidade, float precoCusto) {
    if (quantidade <= 0 || precoCusto <= 0.0f) {
        // Validação básica: não se pode adicionar um produto novo sem quantidade ou preço
        return -1;
    }
    Produto novoProduto(nome, quantidade, precoCusto);
    novoProduto.setId(proximoIdProduto);
    produtos.push_back(novoProduto);
    return proximoIdProduto++;
}

// Atualiza o stock e/ou preço de custo de um produto EXISTENTE.
// Retorna true se atualizado, false se o produto não for encontrado.
bool Loja::atualizarProduto(const string& nome, int quantidadeAdicional, float novoPrecoCusto) {
    Produto* produtoExistente = buscarProdutoPorNome(nome);
    if (produtoExistente) {
        if (quantidadeAdicional > 0) {
            produtoExistente->adicionarEstoque(quantidadeAdicional);
        }
        if (novoPrecoCusto > 0.0f) { // Permite atualizar para 0 se for o caso, mas >0 é mais comum
            produtoExistente->setPrecoCusto(novoPrecoCusto);
        }
        return true; // Produto atualizado
    }
    return false; // Produto não encontrado para atualização
}


// Remove um produto pelo ID
bool Loja::removerProduto(int id) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });

    if (it != produtos.end()) {
        produtos.erase(it);
        return true;
    }
    return false;
}

// Adiciona estoque a um produto existente
bool Loja::adicionarEstoque(int id, int quantidade) {
    Produto* produto = buscarProduto(id);
    if (produto) {
        produto->adicionarEstoque(quantidade);
        return true;
    }
    return false;
}

// Atualiza o preço de custo de um produto
bool Loja::atualizarPrecoProduto(int id, float novoPrecoCusto) {
    Produto* produto = buscarProduto(id);
    if (produto && novoPrecoCusto > 0.0f) {
        produto->setPrecoCusto(novoPrecoCusto);
        return true;
    }
    return false;
}

// Lista todos os produtos em estoque
void Loja::listarProdutos() const {
    cout << "\n";
    cout << "+===============================================================================+\n";
    cout << "|                              PRODUTOS EM STOCK                                |\n";
    cout << "+===============================================================================+\n";
    cout << "\n";

    if (produtos.empty()) {
        cout << "Nenhum produto cadastrado.\n\n";
        return;
    }

    cout << "+====+========================================+=====+=============+=============+\n";
    cout << "| ID |                PRODUTO                 | QTD | PRECO UNIT. | PRECO VENDA |\n";
    cout << "+====+========================================+=====+=============+=============+\n";

    for (const auto& produto : produtos) {
        string nomeTruncado = produto.getNome();
        if (nomeTruncado.length() > 28) {
            nomeTruncado = nomeTruncado.substr(0, 25) + "...";
        }

        cout << "| " << right << setw(2) << produto.getId() << " | "
            << left << setw(38) << nomeTruncado << " | "
            << right << setw(3) << produto.getQuantidade() << " | "
            << right << setw(10) << fixed << setprecision(2) << produto.getPrecoCusto() << "€ | "
            << right << setw(10) << fixed << setprecision(2) << produto.getPrecoVenda() << "€ |\n";
    }

    cout << "+====+========================================+=====+=============+=============+\n";
    cout << "\n";
}

// Gera relatório do estoque atual
void Loja::relatorioStock() const {
    cout << "\n";
    cout << "+========================================================================+\n";
    cout << "|                           RELATORIO DE STOCK                           |\n";
    cout << "=========================================================================+\n";
    cout << "\n";

    if (produtos.empty()) {
        cout << "Nenhum produto em estoque.\n\n";
        return;
    }

    cout << "+====+==============================+=====+=============+================+\n";
    cout << "| ID |           PRODUTO            | QTD | PRECO UNIT. |  VALOR TOTAL   |\n";
    cout << "+====+==============================+=====+=============+================+\n";

    int totalQuantidade = 0;
    float valorTotalEstoque = 0.0f;

    for (const auto& produto : produtos) {
        string nomeTruncado = produto.getNome();
        if (nomeTruncado.length() > 28) {
            nomeTruncado = nomeTruncado.substr(0, 25) + "...";
        }

        // Adiciona indicador de status do estoque
        string status = "";
        if (produto.getQuantidade() == 0) {
            status = " [SEM]";
            nomeTruncado = nomeTruncado.substr(0, 23) + status;
        }
        else if (produto.getQuantidade() <= 5) {
            status = " [BAIXO]";
            nomeTruncado = nomeTruncado.substr(0, 20) + status;
        }

        float valorTotal = produto.getQuantidade() * produto.getPrecoCusto();
        totalQuantidade += produto.getQuantidade();
        valorTotalEstoque += valorTotal;


        cout << "| " << right << setw(2) << produto.getId() << " | "
            << left << setw(28) << nomeTruncado << " | "
            << right << setw(3) << produto.getQuantidade() << " | "
            << right << setw(10) << fixed << setprecision(2) << produto.getPrecoCusto() << "€ | "
            << right << setw(13) << fixed << setprecision(2) << valorTotal << "€ |\n";
    }

    cout << "+====+==============================+=====+=============+================+\n";
    cout << "|         TOTAL GERAL               | " << right << setw(3) << totalQuantidade << " |             | "
        << right << setw(13) << fixed << setprecision(2) << valorTotalEstoque << "€ |\n";
    cout << "+====+==============================+=====+=============+================+\n";
    cout << "\n";
    cout << "Legenda: [BAIXO] = Stock baixo (<=5)  [SEM] = Sem stock\n";
    cout << "\n";
}

// Cria uma nova venda com FIFO automático
int Loja::criarVenda(int idCliente) {
    Venda novaVenda(proximoNumeroFatura++, idCliente);  // Incrementa logo o número

    // FIFO automático - deque cuida da lógica circular
    if (vendas.size() >= LIMITE_VENDAS) {
        vendas.pop_front();  // Remove a mais antiga automaticamente
    }
    vendas.push_back(novaVenda);  // Adiciona a nova

    return novaVenda.getNumeroFatura();
}

// Adiciona um item a uma venda existente
bool Loja::adicionarItemVenda(int numeroFatura, int idProduto, int quantidade) {
    Venda* venda = buscarVenda(numeroFatura); // Busca a venda pelo número da fatura
    if (!venda) return false; // Retorna falso se a venda não for encontrada

    Produto* produto = buscarProduto(idProduto); // Busca o produto pelo ID
    if (!produto) return false; // Retorna falso se o produto não for encontrado

    if (!produto->temEstoqueSuficiente(quantidade)) { // Verifica se há estoque suficiente
        return false; // Retorna falso se não houver estoque suficiente
    }

    // Verifica se o produto já existe na venda
    ItemVenda* itemExistente = nullptr; // Inicializa um ponteiro para um item de venda existente como nulo
    for (int i = 0; i < venda->getNumItens(); ++i) { // Itera sobre os itens existentes na venda
        if (venda->getItem(i)->idProduto == idProduto) { // Se o ID do produto do item existente for igual ao ID do produto a ser adicionado
            itemExistente = venda->getItem(i); // Atribui o item existente ao ponteiro
            break; // Sai do loop
        }
    }

    if (itemExistente) {
        // Se o produto existir, atualiza sua quantidade e total
        itemExistente->quantidade += quantidade; // Adiciona a nova quantidade à quantidade existente
        itemExistente->total = itemExistente->quantidade * produto->getPrecoVenda(); // Recalcula o total do item, assumindo que o total deve ser baseado no preço de venda do produto
    }
    else {
        // Se o produto não existir, adiciona um novo item
        venda->adicionarItem(idProduto, produto->getNome(), quantidade, produto->getPrecoCusto()); // Adiciona um novo item à venda
    }

    produto->removerEstoque(quantidade); // Remove a quantidade do estoque do produto
    return true; // Retorna verdadeiro indicando sucesso
}

// Finaliza uma venda processando o pagamento
bool Loja::finalizarVenda(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) return false;

    if (!venda->exibirCheckout()) {
        return false; // Venda cancelada
    }

    venda->processarPagamento(valorEntregue);
    venda->imprimirTalao();
    return true;
}

// Finaliza uma venda sem exibir checkout (para vendas iniciais)
bool Loja::finalizarVendaSilenciosa(int numeroFatura, float valorEntregue) {
    Venda* venda = buscarVenda(numeroFatura);
    if (!venda) return false;

    venda->processarPagamento(valorEntregue);
    return true;
}

// Gera relatório de vendas por produto
void Loja::relatorioVendasPorProduto(int idProduto) const {
    const Produto* produto = buscarProduto(idProduto);
    if (!produto) {
        cout << "Produto não encontrado!\n";
        return;
    }

    cout << "\n";
    cout << "+==============================================================================+\n";
    cout << "|                      RELATORIO DE VENDAS POR PRODUTO                         |\n";
    cout << "+==============================================================================+\n";
    cout << "Produto: " << produto->getNome() << " (ID: " << idProduto << ")\n";
    cout << "\n";

    cout << "+===========+==================+==========+==========+=========================+\n";
    cout << "| FATURA N° |       DATA       | CLIENTE  |   QTD    |      VALOR TOTAL        |\n";
    cout << "+===========+==================+==========+==========+=========================+\n";

    int totalQuantidade = 0;
    float valorTotal = 0.0f;
    int totalVendas = 0;

    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            for (int i = 0; i < venda.getNumItens(); i++) {
                const ItemVenda* item = venda.getItem(i);
                if (item && item->idProduto == idProduto) {
                    cout << "| " << right << setw(9) << venda.getNumeroFatura() << " | "
                        << left << setw(14) << venda.getData() << " | "
                        << right << setw(8) << venda.getNumeroCliente() << " | "
                        << right << setw(8) << item->quantidade << " | "
                        << right << setw(18) << fixed << setprecision(2) << item->total << "€     |\n";

                    totalQuantidade += item->quantidade;
                    valorTotal += item->total;
                    totalVendas++;
                }
            }
        }
    }
    cout << "+===========+==================+==========+==========+=========================+\n";
    if (totalVendas == 0) {
        cout << "|                          NENHUMA VENDA REGISTRADA                            |\n";
    }
    else {
        cout << "+==================================+====================+======================+\n";
        cout << "|   TOTAL DE VENDAS REALIZADAS     | QTD TOTAL VENDIDA  |      VALOR TOTAL     |\n";
        cout << "+==================================+====================+======================+\n";
        cout << right << setw(34) << totalVendas << " | "
            << right << setw(18) << totalQuantidade << " | "
            << right << setw(19) << fixed << setprecision(2) << valorTotal << "€ |\n";
    }

    cout << "+==================================+====================+======================+\n";
    cout << "\n";
}

// Gera relatório total de vendas
void Loja::relatorioTotalVendas() const {
    cout << "\n";
    cout << "+==============================================================================+\n";
    cout << "|                          RELATORIO TOTAL DE VENDAS                           |\n";
    cout << "+==============================================================================+\n";
    cout << "\n";

    cout << "+===========+==================+===========+==========+========================+\n";
    cout << "| FATURA N° |       DATA       |  CLIENTE  |  ITENS   |    VALOR POR FATURA    |\n";
    cout << "+===========+==================+===========+==========+========================+\n";

    int totalVendas = 0;
    float valorTotalGeral = 0.0f;

    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            cout << "| " << right << setw(10) << venda.getNumeroFatura() << " | "
                << left << setw(14) << venda.getData() << " | "
                << right << setw(8) << venda.getNumeroCliente() << " | "
                << right << setw(8) << venda.getNumItens() << " | "
                << right << setw(21) << fixed << setprecision(2) << venda.getTotalComIVA() << "€ |\n";

            totalVendas++;
            valorTotalGeral += venda.getTotalComIVA();
        }
    }
    cout << "+===========+==================+===========+==========+========================+\n";

    if (totalVendas == 0) {
        cout << "|                          NENHUMA VENDA REGISTRADA                            |\n";
    }
    else {
        cout << "+===========+=============================+=============+======================+\n";
        cout << "|   TOTAL   | " << totalVendas << " vendas realizadas         | VALOR TOTAL |"
            << right << setw(20) << fixed << setprecision(2) << valorTotalGeral << "€ |\n";
    }

    cout << "+===========+=============================+=============+======================+\n";
    cout << "\n";
}

// Gera relatório de estatísticas de vendas (produto mais/menos vendido, lucros, melhor cliente)
void Loja::relatorioEstatisticasVendas() const {
    cout << "\n";
    cout << "+=======================================================================================+\n";
    cout << "|                               ESTATISTICAS DE VENDAS                                  |\n";
    cout << "+=======================================================================================+\n";
    cout << "\n";

    // Mapas para armazenar estatísticas
    map<int, int> quantidadePorProduto;
    map<int, float> valorPorProduto;
    map<int, float> lucroPorProduto;
    map<int, float> valorPorCliente;

    // Coleta dados de todas as vendas
    for (const auto& venda : vendas) {
        if (venda.getNumItens() > 0) {
            // Soma valor por cliente
            valorPorCliente[venda.getNumeroCliente()] += venda.getTotalComIVA();

            // Processa cada item da venda
            for (int i = 0; i < venda.getNumItens(); i++) {
                const ItemVenda* item = venda.getItem(i);
                if (item) {
                    quantidadePorProduto[item->idProduto] += item->quantidade;
                    valorPorProduto[item->idProduto] += item->total;

                    // Calcula lucro (preço venda - preço custo) * quantidade
                    const Produto* produto = buscarProduto(item->idProduto);
                    if (produto) {
                        float lucroUnitario = produto->getPrecoVenda() - produto->getPrecoCusto();
                        lucroPorProduto[item->idProduto] += lucroUnitario * item->quantidade;
                    }
                }
            }
        }
    }

    if (quantidadePorProduto.empty()) {
        cout << "Nenhuma venda registrada para gerar estatisticas.\n\n";
        return;
    }

    // Encontra produto mais vendido
    int produtoMaisVendido = 0;
    int maiorQuantidade = 0;
    for (const auto& par : quantidadePorProduto) {
        if (par.second > maiorQuantidade) {
            maiorQuantidade = par.second;
            produtoMaisVendido = par.first;
        }
    }

    // Encontra produto menos vendido
    int produtoMenosVendido = 0;
    int menorQuantidade = INT_MAX;
    for (const auto& par : quantidadePorProduto) {
        if (par.second < menorQuantidade) {
            menorQuantidade = par.second;
            produtoMenosVendido = par.first;
        }
    }

    // Encontra cliente que mais comprou
    int melhorCliente = 0;
    float maiorValorCliente = 0.0f;
    for (const auto& par : valorPorCliente) {
        if (par.second > maiorValorCliente) {
            maiorValorCliente = par.second;
            melhorCliente = par.first;
        }
    }

    // Exibe resultados
    cout << "+=======================================================================================+\n";
    cout << "|                                 PRODUTO MAIS VENDIDO                                  |\n";
    cout << "+=======================================================================================+\n";
    const Produto* prodMaisVendido = buscarProduto(produtoMaisVendido);
    if (prodMaisVendido) {
        cout << "Produto: " << prodMaisVendido->getNome() << " (ID: " << produtoMaisVendido << ")\n";
        cout << "Quantidade vendida: " << maiorQuantidade << " unidades\n";
        cout << "Valor total vendido: " << fixed << setprecision(2) << valorPorProduto[produtoMaisVendido] << "€\n";
        cout << "Lucro gerado: " << fixed << setprecision(2) << lucroPorProduto[produtoMaisVendido] << "€\n";
    }
    cout << "\n";

    cout << "+=======================================================================================+\n";
    cout << "|                                PRODUTO MENOS VENDIDO                                  |\n";
    cout << "+=======================================================================================+\n";
    const Produto* prodMenosVendido = buscarProduto(produtoMenosVendido);
    if (prodMenosVendido) {
        cout << "Produto: " << prodMenosVendido->getNome() << " (ID: " << produtoMenosVendido << ")\n";
        cout << "Quantidade vendida: " << menorQuantidade << " unidades\n";
        cout << "Valor total vendido: " << fixed << setprecision(2) << valorPorProduto[produtoMenosVendido] << "€\n";
    }
    cout << "\n";

    cout << "+=======================================================================================+\n";
    cout << "|                               CLIENTE QUE MAIS COMPROU                                |\n";
    cout << "+=======================================================================================+\n";
    const Cliente* clienteTop = buscarCliente(melhorCliente);
    if (clienteTop) {
        cout << "Cliente: " << clienteTop->getNome() << " (ID: " << melhorCliente << ")\n";
        cout << "Valor total comprado: " << fixed << setprecision(2) << maiorValorCliente << "€\n";
        cout << "Telefone: " << clienteTop->getTelefone() << "\n";
    }
    cout << "\n";

    cout << "+=======================================================================================+\n";
    cout << "|                                      RESUMO GERAL                                     |\n";
    cout << "+=======================================================================================+\n";
    cout << "Total de produtos diferentes vendidos: " << static_cast<int>(quantidadePorProduto.size()) << "\n";
    cout << "Total de clientes ativos: " << static_cast<int>(valorPorCliente.size()) << "\n";

    float lucroTotal = 0.0f;
    for (const auto& par : lucroPorProduto) {
        lucroTotal += par.second;
    }
    cout << "Lucro total gerado: " << fixed << setprecision(2) << lucroTotal << "€\n";
    cout << "\n";
}

// Inicializa a loja com dados de exemplo
void Loja::inicializarDadosIniciais() {
    // Adicionar clientes iniciais
    adicionarCliente("Joao Silva", "912345678", "Rua das Flores, 123", "Lisboa");
    adicionarCliente("Maria Santos", "923456789", "Av. da Liberdade, 456", "Porto");
    adicionarCliente("Pedro Costa", "934567890", "Rua do Comercio, 789", "Coimbra");
    adicionarCliente("Ana Rodrigues", "945678901", "Praca da Republica, 321", "Braga");
    adicionarCliente("Carlos Mendes", "956789012", "Rua Central, 654", "Faro");
    adicionarCliente("Sofia Pereira", "967890123", "Av. dos Aliados, 987", "Aveiro");
    adicionarCliente("Miguel Ferreira", "978901234", "Rua da Paz, 147", "Viseu");
    adicionarCliente("Catarina Lopes", "989012345", "Largo do Municipio, 258", "Evora");

    // Adicionar produtos iniciais
    adicionarNovoProduto("Placa Mae ASUS B450", 15, 89.99f);
    adicionarNovoProduto("Processador AMD Ryzen 5", 12, 199.99f);
    adicionarNovoProduto("Memoria RAM 16GB DDR4", 25, 79.99f);
    adicionarNovoProduto("Disco SSD 1TB NVMe", 20, 87.94f);
    adicionarNovoProduto("Placa Grafica RTX 3060", 8, 399.99f);
    adicionarNovoProduto("Fonte 650W 80+ Bronze", 18, 71.95f);
    adicionarNovoProduto("Caixa ATX Mid Tower", 10, 59.99f);
    adicionarNovoProduto("Monitor 24'' Full HD", 15, 143.91f);
    adicionarNovoProduto("Teclado Mecanico RGB", 25, 89.99f);
    adicionarNovoProduto("Cooler CPU", 30, 29.99f);
    adicionarNovoProduto("Webcam Full HD", 20, 35.50f);
    adicionarNovoProduto("Rato Gaming", 30, 25.00f);
    adicionarNovoProduto("Headset com Microfone", 15, 49.99f);
    adicionarNovoProduto("Router Wi-Fi 6", 10, 75.00f);
    adicionarNovoProduto("Cartucho Tinta Preto", 50, 15.00f);
    adicionarNovoProduto("Pen Drive 64GB", 40, 10.00f);
    adicionarNovoProduto("Disco Externo 2TB", 8, 95.00f);
    adicionarNovoProduto("Cabo HDMI 2m", 60, 8.00f);
    adicionarNovoProduto("Adaptador USB-C para HDMI", 25, 18.00f);

    // Criar vendas iniciais
    criarVendasIniciais();
}

// Função auxiliar para criar vendas iniciais de exemplo.
void Loja::criarVendasIniciais() {
    // Venda 1: João Silva (ID 1)
    int fatura1 = criarVenda(1);
    adicionarItemVenda(fatura1, 1, 1);  // Placa Mãe ASUS B450
    adicionarItemVenda(fatura1, 2, 1);  // Processador AMD Ryzen 5
    adicionarItemVenda(fatura1, 3, 2);  // Memoria RAM 16GB DDR4
    finalizarVendaSilenciosa(fatura1, 500.0f);

    // Venda 2: Maria Santos (ID 2)
    int fatura2 = criarVenda(2);
    adicionarItemVenda(fatura2, 8, 1);  // Monitor 24'' Full HD
    adicionarItemVenda(fatura2, 7, 1);  // Caixa ATX Mid Tower
    finalizarVendaSilenciosa(fatura2, 250.0f);

    // Venda 3: Pedro Costa (ID 3)
    int fatura3 = criarVenda(3);
    adicionarItemVenda(fatura3, 4, 2);  // Disco SSD 1TB NVMe
    adicionarItemVenda(fatura3, 6, 1);  // Fonte 650W 80+ Bronze
    finalizarVendaSilenciosa(fatura3, 300.0f);

    // Venda 4: Ana Rodrigues (ID 4)
    int fatura4 = criarVenda(4);
    adicionarItemVenda(fatura4, 5, 1);  // Placa Grafica RTX 3060
    finalizarVendaSilenciosa(fatura4, 520.0f);

    // Venda 5: Carlos Mendes (ID 5)
    int fatura5 = criarVenda(5);
    adicionarItemVenda(fatura5, 7, 1);  // Caixa ATX Mid Tower
    adicionarItemVenda(fatura5, 10, 2); // Cooler CPU
    finalizarVendaSilenciosa(fatura5, 150.0f);

    // Venda 6: Sofia Pereira (ID 6)
    int fatura6 = criarVenda(6);
    adicionarItemVenda(fatura6, 11, 1); // Webcam Full HD
    adicionarItemVenda(fatura6, 12, 1); // Rato Gaming
    finalizarVendaSilenciosa(fatura6, 70.0f);

    // Venda 7: Miguel Ferreira (ID 7)
    int fatura7 = criarVenda(7);
    adicionarItemVenda(fatura7, 13, 1); // Headset com Microfone
    finalizarVendaSilenciosa(fatura7, 60.0f);

    // Venda 8: Catarina Lopes (ID 8)
    int fatura8 = criarVenda(8);
    adicionarItemVenda(fatura8, 14, 1); // Router Wi-Fi 6
    finalizarVendaSilenciosa(fatura8, 90.0f);

    // Venda 9: Rui Almeida (ID 9)
    int fatura9 = criarVenda(9);
    adicionarItemVenda(fatura9, 15, 1); // Impressora Multifunções
    adicionarItemVenda(fatura9, 16, 2); // Cartucho Tinta Preto
    finalizarVendaSilenciosa(fatura9, 180.0f);

    // Venda 10: Beatriz Sousa (ID 10)
    int fatura10 = criarVenda(10);
    adicionarItemVenda(fatura10, 17, 5); // Pen Drive 64GB
    adicionarItemVenda(fatura10, 18, 1); // Disco Externo 2TB
    finalizarVendaSilenciosa(fatura10, 170.0f);

    // Venda 11: João Silva (ID 1)
    int fatura11 = criarVenda(1);
    adicionarItemVenda(fatura11, 19, 5); // Cabo HDMI 2m
    finalizarVendaSilenciosa(fatura11, 50.0f);

    // Venda 12: Maria Santos (ID 2)
    int fatura12 = criarVenda(2);
    adicionarItemVenda(fatura12, 20, 2); // Adaptador USB-C para HDMI
    finalizarVendaSilenciosa(fatura12, 45.0f);

    // Venda 13: Pedro Costa (ID 3)
    int fatura13 = criarVenda(3);
    adicionarItemVenda(fatura13, 9, 1); // Teclado Mecanico RGB
    finalizarVendaSilenciosa(fatura13, 110.0f);

    // Venda 14: Ana Rodrigues (ID 4)
    int fatura14 = criarVenda(4);
    adicionarItemVenda(fatura14, 1, 1); // Placa Mae ASUS B450
    adicionarItemVenda(fatura14, 4, 1); // Disco SSD 1TB NVMe
    finalizarVendaSilenciosa(fatura14, 220.0f);

    // Venda 15: Carlos Mendes (ID 5)
    int fatura15 = criarVenda(5);
    adicionarItemVenda(fatura15, 12, 2); // Rato Gaming
    finalizarVendaSilenciosa(fatura15, 60.0f);

    // Venda 16: Sofia Pereira (ID 6)
    int fatura16 = criarVenda(6);
    adicionarItemVenda(fatura16, 16, 3); // Cartucho Tinta Preto
    finalizarVendaSilenciosa(fatura16, 55.0f);

    // Venda 17: Miguel Ferreira (ID 7)
    int fatura17 = criarVenda(7);
    adicionarItemVenda(fatura17, 5, 1); // Placa Grafica RTX 3060
    finalizarVendaSilenciosa(fatura17, 520.0f);

    // Venda 18: Catarina Lopes (ID 8)
    int fatura18 = criarVenda(8);
    adicionarItemVenda(fatura18, 8, 1); // Monitor 24'' Full HD
    finalizarVendaSilenciosa(fatura18, 180.0f);

    // Venda 19: Rui Almeida (ID 9)
    int fatura19 = criarVenda(9);
    adicionarItemVenda(fatura19, 1, 1); // Placa Mae ASUS B450
    finalizarVendaSilenciosa(fatura19, 110.0f);

    // Venda 20: Beatriz Sousa (ID 10)
    int fatura20 = criarVenda(10);
    adicionarItemVenda(fatura20, 2, 1); // Processador AMD Ryzen 5
    finalizarVendaSilenciosa(fatura20, 250.0f);

    // Venda 21: João Silva (ID 1)
    int fatura21 = criarVenda(1);
    adicionarItemVenda(fatura21, 10, 2); // Cooler CPU
    finalizarVendaSilenciosa(fatura21, 75.0f);

    // Venda 22: Pedro Costa (ID 3)
    int fatura22 = criarVenda(3);
    adicionarItemVenda(fatura22, 11, 1); // Webcam Full HD
    adicionarItemVenda(fatura22, 13, 1); // Headset com Microfone
    finalizarVendaSilenciosa(fatura22, 100.0f);

    // Venda 23: Carlos Mendes (ID 5)
    int fatura23 = criarVenda(5);
    adicionarItemVenda(fatura23, 18, 1); // Disco Externo 2TB
    finalizarVendaSilenciosa(fatura23, 120.0f);

    // Venda 24: Miguel Ferreira (ID 7)
    int fatura24 = criarVenda(7);
    adicionarItemVenda(fatura24, 19, 10); // Cabo HDMI 2m
    finalizarVendaSilenciosa(fatura24, 100.0f);

    // Venda 25: Rui Almeida (ID 9)
    int fatura25 = criarVenda(9);
    adicionarItemVenda(fatura25, 6, 1); // Fonte 650W 80+ Bronze
    adicionarItemVenda(fatura25, 7, 1); // Caixa ATX Mid Tower
    finalizarVendaSilenciosa(fatura25, 160.0f);
}

// Busca um cliente pelo ID (versão const)
const Cliente* Loja::buscarCliente(int id) const {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });
    return (it != clientes.end()) ? &(*it) : nullptr;
}

// Busca um cliente pelo ID (versão não-const)
Cliente* Loja::buscarCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
        [id](const Cliente& c) { return c.getId() == id; });
    return (it != clientes.end()) ? &(*it) : nullptr;
}

// Busca um produto pelo ID (versão const)
const Produto* Loja::buscarProduto(int id) const {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });
    return (it != produtos.end()) ? &(*it) : nullptr;
}

// Busca um produto pelo ID (versão não-const)
Produto* Loja::buscarProduto(int id) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [id](const Produto& p) { return p.getId() == id; });
    return (it != produtos.end()) ? &(*it) : nullptr;
}

// Busca uma venda pelo número da fatura (versão const)
const Venda* Loja::buscarVenda(int numeroFatura) const {
    auto it = find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });
    return (it != vendas.end()) ? &(*it) : nullptr;
}

// Busca uma venda pelo número da fatura (versão não-const)
Venda* Loja::buscarVenda(int numeroFatura) {
    auto it = find_if(vendas.begin(), vendas.end(),
        [numeroFatura](const Venda& v) { return v.getNumeroFatura() == numeroFatura; });
    return (it != vendas.end()) ? &(*it) : nullptr;
}


// Adiciona um novo cliente
int Loja::adicionarCliente(const string& nome, const string& telefone, const string& morada, const string& cidade) {
    Cliente novoCliente(nome, telefone, morada, cidade);
    novoCliente.setId(proximoIdCliente);
    clientes.push_back(novoCliente);
    return proximoIdCliente++;
}


// Busca um produto pelo nome (versão não-const)
Produto* Loja::buscarProdutoPorNome(const string& nome) {
    auto it = find_if(produtos.begin(), produtos.end(),
        [&nome](const Produto& p) { return compararStringsIgnorarCase(p.getNome(), nome); });
    return (it != produtos.end()) ? &(*it) : nullptr;
}
