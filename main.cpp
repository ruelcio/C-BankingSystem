#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>

#include "ContaBancaria.hpp"
#include "persistencia.hpp"

// Vetor global para armazenar contas
std::vector<ContaBancaria> contas;
std::string nomeArquivo = "contas.txt";

// Função para abrir conta (interage com o usuário e cria a conta)
void abrirConta() {
    std::string nome, bi, nacionalidade, nascimento;
    std::cout << "Nome completo: ";
    std::getline(std::cin, nome);
    std::cout << "Numero do BI: ";
    std::getline(std::cin, bi);
    std::cout << "Nacionalidade: ";
    std::getline(std::cin, nacionalidade);
    std::cout << "Data de nascimento (DD/MM/AAAA): ";
    std::getline(std::cin, nascimento);

    int numeroConta = contas.size() + 1;  
    ContaBancaria novaConta(numeroConta, nome, bi, nacionalidade, nascimento);
    contas.push_back(novaConta);

    std::cout << "Conta criada com sucesso! Numero da conta: " << numeroConta << std::endl;
}

// Função para listar todas as contas
void listarContas() {
    if (contas.empty()) {
        std::cout << "Nenhuma conta cadastrada.\n";
        return;
    }
    for (const auto& conta : contas) {
        std::cout << "\n";
        conta.mostrarDados();
        std::cout << "-----------------------\n";
    }
}

// Função para exibir o menu
void exibirMenu() {
    std::cout << "====== UmaBankingSystem ======\n";
    std::cout << "1. Abrir Conta\n";
    std::cout << "2. Depositar\n"; 
    std::cout << "3. Levantar\n";
    std::cout << "4. Consultar Contas\n";
    std::cout << "5. Transferir\n";
    std::cout << "6. Pagar Servicos\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma Opcao: ";
}

void depositar(std::vector<ContaBancaria>& contas) {
    int numeroConta;
    double valor;

    std::cout << "Digite o numero da conta para deposito: ";
    std::cin >> numeroConta;

    // Buscar conta
    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        std::cout << "Conta nao encontrada!\n";
        return;
    }

    std::cout << "Digite o valor do deposito: ";
    std::cin >> valor;

    if (valor <= 0) {
        std::cout << "Valor invalido para deposito.\n";
        return;
    }

    // Atualizar saldo
    double saldoAtual = it -> getSaldo();
    it->setSaldo(saldoAtual + valor);

    std::cout << "Deposito realizado com sucesso. Novo saldo: Kz " << it -> getSaldo() << "\n";
}

void realizarLevantamento(std::vector <ContaBancaria>& contas) {
    int numeroConta;
    double valor;

    std::cout << "Digite o numero da conta para levantamento: ";
    std::cin >> numeroConta;

    auto it = std::find_if(contas.begin(), contas.end(), [numeroConta](const ContaBancaria& c) {
        return c.getNumeroConta() == numeroConta;
    });

    if (it != contas.end()) {
        std::cout << "Digite o valor do levantamento: ";
        std::cin >> valor;

        if (valor <= 0) {
            std::cout << "Valor invalido!\n";
            return;
        }

        if (it->getSaldo() >= valor) {
            it->setSaldo(it->getSaldo() - valor);
            std::cout << "Levantamento realizado com sucesso. Novo saldo: Kz " << it->getSaldo() << "\n";

            salvarContasEmArquivo(contas, "contas.txt");
        } else {
            std::cout << "Saldo insuficiente!\n";
        }
    } else {
        std::cout << "Conta nao encontrada.\n";
    }
}

void realizarTransferencia(std::vector<ContaBancaria>& contas, const std::string& nomeArquivo)
{
    int numeroContaOrigem;
    int numeroContaDestino;
    double valor;

    std::cout << "Digite o seu número de conta: ";
    std::cin >> numeroContaOrigem;
    std::cout << "Digite o número da conta destino: ";
    std::cin >> numeroContaDestino;

    auto itOrigem = std::find_if(contas.begin(), contas.end(),
                    [numeroContaOrigem](const ContaBancaria& conta)
    {
        return conta.getNumeroConta() == numeroContaOrigem;
    });

    if (itOrigem == contas.end())
    {
        std::cout << "Sua conta não foi encontrada.\n";
        return;
    }

    auto itDestino = std::find_if(contas.begin(), contas.end(),
                    [numeroContaDestino](const ContaBancaria& conta)
    {
        return conta.getNumeroConta() == numeroContaDestino;
    });

    if (itDestino == contas.end())
    {
        std::cout << "Conta destino não encontrada.\n";
        return;
    }

    std::cout << "Valor a transferir: ";
    std::cin >> valor;

    if (valor <= 0)
    {
        std::cout << "Valor inválido!\n";
        return;
    }

    if (itOrigem->getSaldo() < valor)
    {
        std::cout << "Saldo insuficiente na conta.\n";
        return;
    }

    // Atualiza os saldos usando iteradores (que atuam como ponteiros)
    itOrigem->setSaldo(itOrigem->getSaldo() - valor);
    itDestino->setSaldo(itDestino->getSaldo() + valor);

    std::cout << "Transferência realizada com sucesso.\n";
    std::cout << "Novo saldo da sua conta: " << std::fixed << std::setprecision(2) << itOrigem->getSaldo() << " Kz\n";
    std::cout << "Novo saldo da conta destino: " << std::fixed << std::setprecision(2) << itDestino->getSaldo() << " Kz\n";

    // Salva as contas atualizadas no arquivo
    salvarContasEmArquivo(contas, nomeArquivo);
}

void realizarPagamento(std::vector<ContaBancaria>& contas, const std::string& nomeArquivo) {
    int numeroConta;
    int opcaoServico;
    double valorPagamento;
    std::string nomeServico;

    std::cout << "Digite o numero da sua conta: ";
    std::cin >> numeroConta;

    auto it = std::find_if(contas.begin(), contas.end(), [numeroConta](const ContaBancaria& conta) {
        return conta.getNumeroConta() == numeroConta;
    });

    if (it == contas.end()) {
        std::cout << "Conta nao encontrada.\n";
        return;
    }

    // Menu de serviços
    std::cout << "Selecione o servico a pagar:\n";
    std::cout << "1. Energia\n";
    std::cout << "2. Agua\n";
    std::cout << "3. Internet\n";
    std::cout << "Opcao: ";
    std::cin >> opcaoServico;

    switch (opcaoServico) {
        case 1: nomeServico = "Energia"; break;
        case 2: nomeServico = "Agua"; break;
        case 3: nomeServico = "Internet"; break;
        default:
            std::cout << "Servico invalido!\n";
            return;
    }

    std::cout << "Digite o valor do pagamento: ";
    std::cin >> valorPagamento;

    if (valorPagamento <= 0) {
        std::cout << "Valor invalido!\n";
        return;
    }

    if (it->getSaldo() < valorPagamento) {
        std::cout << "Saldo insuficiente para realizar o pagamento.\n";
        return;
    }

    // Realiza o pagamento
    it->setSaldo(it->getSaldo() - valorPagamento);

    // Data atual
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    // Recibo
    std::cout << "\n===== Recibo de Pagamento =====\n";
    std::cout << "Data: " << (now->tm_mday < 10 ? "0" : "") << now->tm_mday << "/"
              << (now->tm_mon + 1 < 10 ? "0" : "") << (now->tm_mon + 1) << "/"
              << (now->tm_year + 1900) << "\n";
    std::cout << "Nome do titular: " << it->getNomeCompleto() << "\n";
    std::cout << "Servico pago: " << nomeServico << "\n";
    std::cout << "Valor: " << std::fixed << std::setprecision(2) << valorPagamento << " Kz\n";
    std::cout << "Novo saldo: " << it->getSaldo() << " Kz\n";
    std::cout << "===============================\n";

    // Atualiza arquivo
    salvarContasEmArquivo(contas, nomeArquivo);
}


int main() {
    carregarContasDoArquivo(contas, "contas.txt");

    int opcao;
    do {
        exibirMenu();
        std::cin >> opcao;
        std::cin.ignore();  // Limpar o '\n' do buffer antes do getline

        switch (opcao) {
            case 1:
                abrirConta();
                break;
            case 2:
                depositar(contas);
                salvarContasEmArquivo(contas, nomeArquivo);
                break;
            case 3:
                realizarLevantamento(contas);
                salvarContasEmArquivo(contas, nomeArquivo);
                break;
            case 4:
                listarContas();
                break;
            case 5:
                realizarTransferencia(contas, nomeArquivo);
                salvarContasEmArquivo(contas, nomeArquivo);
            case 6:
                realizarPagamento(contas, nomeArquivo);
                salvarContasEmArquivo(contas, nomeArquivo);
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida, tente novamente.\n";
        }
        std::cout << std::endl;
    } while (opcao != 0);

    salvarContasEmArquivo(contas, "contas.txt");

    return 0;
}
