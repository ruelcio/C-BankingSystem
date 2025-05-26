#include "banco.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

Banco::Banco(const std::string& arquivo) : nomeArquivo(arquivo) {
    contas = persistencia.carregarContas(nomeArquivo);
}

void Banco::abrirConta() {
    std::string nome, bi, nacionalidade, nascimento;
    std::cout << "\nNome completo: ";
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
    persistencia.salvarContasEmArquivo(contas, nomeArquivo);

    std::cout << "\nConta criada com sucesso!" << std::endl;
    std::cout << "Numero da conta: " << numeroConta << std::endl;
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.get();
}

void Banco::listarContas() const {
    if (contas.empty()) {
        std::cout << "\nNenhuma conta cadastrada.\n";
    } else {
        for (const auto& conta : contas) {
            std::cout << "\n";
            conta.mostrarDados();
            std::cout << "------------------------\n";
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.get();
}

void Banco::depositar() {
    int numeroConta;
    double valor;

    std::cout << "\nDigite o numero da conta para deposito: ";
    std::cin >> numeroConta;

    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        std::cout << "\nConta nao encontrada!\n";
    } else {
        std::cout << "Digite o valor do deposito: ";
        std::cin >> valor;

        if (valor <= 0) {
            std::cout << "\nValor invalido para deposito.\n";
        } else {
            it->setSaldo(it->getSaldo() + valor);
            persistencia.salvarContasEmArquivo(contas, nomeArquivo);

            std::cout << "\nDeposito realizado com sucesso!" << std::endl;
            std::cout << "Novo saldo: Kz " << std::fixed << std::setprecision(2) << it->getSaldo() << "\n";
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::realizarLevantamento() {
    int numeroConta;
    double valor;

    std::cout << "\nDigite o numero da conta para levantamento: ";
    std::cin >> numeroConta;

    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        std::cout << "\nConta nao encontrada.\n";
    } else {
        std::cout << "Digite o valor do levantamento: ";
        std::cin >> valor;

        if (valor <= 0) {
            std::cout << "\nValor invalido!\n";
        } else if (it->getSaldo() >= valor) {
            it->setSaldo(it->getSaldo() - valor);
            persistencia.salvarContasEmArquivo(contas, nomeArquivo);
            
            std::cout << "\nLevantamento realizado com sucesso!" << std::endl;
            std::cout << "Novo saldo: Kz " << std::fixed << std::setprecision(2) << it->getSaldo() << "\n";
        } else {
            std::cout << "\nSaldo insuficiente!\n";
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::realizarTransferencia() {
    int numeroContaOrigem, numeroContaDestino;
    double valor;

    std::cout << "\nDigite o seu numero de conta: ";
    std::cin >> numeroContaOrigem;

    std::cout << "Digite o numero da conta destino: ";
    std::cin >> numeroContaDestino;

    auto itOrigem = std::find_if(contas.begin(), contas.end(),
        [numeroContaOrigem](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroContaOrigem;
        });

    if (itOrigem == contas.end()) {
        std::cout << "\nSua conta nao foi encontrada.\n";
    } else {
        auto itDestino = std::find_if(contas.begin(), contas.end(),
            [numeroContaDestino](const ContaBancaria& c) {
                return c.getNumeroConta() == numeroContaDestino;
            });

        if (itDestino == contas.end()) {
            std::cout << "\nConta destino nao encontrada.\n";
        } else {
            std::cout << "Valor a transferir: ";
            std::cin >> valor;

            if (valor <= 0) {
                std::cout << "\nValor invalido!\n";
            } else if (itOrigem->getSaldo() < valor) {
                std::cout << "\nSaldo insuficiente na conta.\n";
            } else {
                itOrigem->setSaldo(itOrigem->getSaldo() - valor);
                itDestino->setSaldo(itDestino->getSaldo() + valor);
                persistencia.salvarContasEmArquivo(contas, nomeArquivo);

                std::cout << "\nTransferencia realizada com sucesso!" << std::endl;
                std::cout << "Novo saldo da sua conta: " << std::fixed << std::setprecision(2) 
                          << itOrigem->getSaldo() << " Kz\n";
                std::cout << "Novo saldo da conta destino: " << std::fixed << std::setprecision(2) 
                          << itDestino->getSaldo() << " Kz\n";
            }
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::realizarPagamento() {
    int numeroConta;
    int opcaoServico;
    double valorPagamento;
    std::string nomeServico;

    std::cout << "\nDigite o numero da sua conta: ";
    std::cin >> numeroConta;

    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        std::cout << "\nConta nao encontrada.\n";
    } else {
        std::cout << "\nServicos disponiveis:\n";
        std::cout << "1. Agua\n";
        std::cout << "2. Luz\n";
        std::cout << "3. Internet\n";
        std::cout << "Escolha o servico: ";
        std::cin >> opcaoServico;

        switch (opcaoServico) {
            case 1: nomeServico = "Agua"; break;
            case 2: nomeServico = "Luz"; break;
            case 3: nomeServico = "Internet"; break;
            default:
                std::cout << "\nOpcao invalida!\n";
                std::cout << "\nPressione ENTER para continuar...";
                std::cin.ignore();
                std::cin.get();
                return;
        }

        std::cout << "Valor do pagamento: ";
        std::cin >> valorPagamento;

        if (valorPagamento <= 0) {
            std::cout << "\nValor invalido!\n";
        } else if (it->getSaldo() < valorPagamento) {
            std::cout << "\nSaldo insuficiente!\n";
        } else {
            it->setSaldo(it->getSaldo() - valorPagamento);
            persistencia.salvarContasEmArquivo(contas, nomeArquivo);

            std::cout << "\nPagamento de " << nomeServico << " realizado com sucesso!" << std::endl;
            std::cout << "Novo saldo: Kz " << std::fixed << std::setprecision(2) << it->getSaldo() << "\n";
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::exibirMenu() const {
    std::cout << "\n=== UMABANKING SYSTEM ===\n\n";
    std::cout << "1. Abrir Conta\n";
    std::cout << "2. Depositar\n";
    std::cout << "3. Levantar\n";
    std::cout << "4. Consultar Contas\n";
    std::cout << "5. Transferir\n";
    std::cout << "6. Pagar Servicos\n";
    std::cout << "0. Sair\n";
    std::cout << "------------------------\n";
    std::cout << "Escolha uma Opcao: ";
}