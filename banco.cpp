#include "banco.hpp"
#include "cores.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

// Limpa a tela
void limparTela() {
    system("cls");
}

// Desenha uma linha
void desenharLinha(int tamanho) {
    std::cout << std::string(tamanho, '=') << std::endl;
}

// Centraliza texto
void centralizarTexto(const std::string& texto, int largura) {
    int espacos = (largura - texto.length()) / 2;
    std::cout << std::string(espacos, ' ') << texto << std::endl;
}

Banco::Banco(const std::string& arquivo) : nomeArquivo(arquivo) {
    contas = persistencia.carregarContas(nomeArquivo);
}

void Banco::abrirConta() {
    limparTela();
    setColor(11); // Ciano
    desenharLinha(50);
    centralizarTexto("ABERTURA DE CONTA", 50);
    desenharLinha(50);
    setColor(7);

    std::string nome, bi, nacionalidade, nascimento;
    std::cout << "\nNome completo: ";
    setColor(14); // Amarelo
    std::getline(std::cin, nome);
    setColor(7);

    std::cout << "Numero do BI: ";
    setColor(14);
    std::getline(std::cin, bi);
    setColor(7);

    std::cout << "Nacionalidade: ";
    setColor(14);
    std::getline(std::cin, nacionalidade);
    setColor(7);

    std::cout << "Data de nascimento (DD/MM/AAAA): ";
    setColor(14);
    std::getline(std::cin, nascimento);
    setColor(7);

    int numeroConta = contas.size() + 1;
    ContaBancaria novaConta(numeroConta, nome, bi, nacionalidade, nascimento);
    contas.push_back(novaConta);
    persistencia.salvarContasEmArquivo(contas, nomeArquivo);

    setColor(10); // Verde
    std::cout << "\nConta criada com sucesso!" << std::endl;
    std::cout << "Numero da conta: " << numeroConta << std::endl;
    setColor(7);
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.get();
}

void Banco::listarContas() const {
    limparTela();
    setColor(11);
    desenharLinha(50);
    centralizarTexto("CONSULTA DE CONTAS", 50);
    desenharLinha(50);
    setColor(7);

    if (contas.empty()) {
        setColor(12); // Vermelho
        std::cout << "\nNenhuma conta cadastrada.\n";
        setColor(7);
    } else {
        for (const auto& conta : contas) {
            setColor(14);
            std::cout << "\n";
            desenharLinha(50);
            conta.mostrarDados();
            desenharLinha(50);
            setColor(7);
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.get();
}

void Banco::depositar() {
    limparTela();
    setColor(11);
    desenharLinha(50);
    centralizarTexto("REALIZAR DEPOSITO", 50);
    desenharLinha(50);
    setColor(7);

    int numeroConta;
    double valor;

    std::cout << "\nDigite o numero da conta para deposito: ";
    setColor(14);
    std::cin >> numeroConta;
    setColor(7);

    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        setColor(12);
        std::cout << "\nConta nao encontrada!\n";
        setColor(7);
    } else {
        std::cout << "Digite o valor do deposito: ";
        setColor(14);
        std::cin >> valor;
        setColor(7);

        if (valor <= 0) {
            setColor(12);
            std::cout << "\nValor invalido para deposito.\n";
            setColor(7);
        } else {
            it->setSaldo(it->getSaldo() + valor);
            persistencia.salvarContasEmArquivo(contas, nomeArquivo);

            setColor(10);
            std::cout << "\nDeposito realizado com sucesso!" << std::endl;
            std::cout << "Novo saldo: Kz " << std::fixed << std::setprecision(2) << it->getSaldo() << "\n";
            setColor(7);
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::realizarLevantamento() {
    limparTela();
    setColor(11);
    desenharLinha(50);
    centralizarTexto("REALIZAR LEVANTAMENTO", 50);
    desenharLinha(50);
    setColor(7);

    int numeroConta;
    double valor;

    std::cout << "\nDigite o numero da conta para levantamento: ";
    setColor(14);
    std::cin >> numeroConta;
    setColor(7);

    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        setColor(12);
        std::cout << "\nConta nao encontrada.\n";
        setColor(7);
    } else {
        std::cout << "Digite o valor do levantamento: ";
        setColor(14);
        std::cin >> valor;
        setColor(7);

        if (valor <= 0) {
            setColor(12);
            std::cout << "\nValor invalido!\n";
            setColor(7);
        } else if (it->getSaldo() >= valor) {
            it->setSaldo(it->getSaldo() - valor);
            persistencia.salvarContasEmArquivo(contas, nomeArquivo);
            
            setColor(10);
            std::cout << "\nLevantamento realizado com sucesso!" << std::endl;
            std::cout << "Novo saldo: Kz " << std::fixed << std::setprecision(2) << it->getSaldo() << "\n";
            setColor(7);
        } else {
            setColor(12);
            std::cout << "\nSaldo insuficiente!\n";
            setColor(7);
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::realizarTransferencia() {
    limparTela();
    setColor(11);
    desenharLinha(50);
    centralizarTexto("REALIZAR TRANSFERENCIA", 50);
    desenharLinha(50);
    setColor(7);

    int numeroContaOrigem, numeroContaDestino;
    double valor;

    std::cout << "\nDigite o seu numero de conta: ";
    setColor(14);
    std::cin >> numeroContaOrigem;
    setColor(7);

    std::cout << "Digite o numero da conta destino: ";
    setColor(14);
    std::cin >> numeroContaDestino;
    setColor(7);

    auto itOrigem = std::find_if(contas.begin(), contas.end(),
        [numeroContaOrigem](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroContaOrigem;
        });

    if (itOrigem == contas.end()) {
        setColor(12);
        std::cout << "\nSua conta nao foi encontrada.\n";
        setColor(7);
    } else {
        auto itDestino = std::find_if(contas.begin(), contas.end(),
            [numeroContaDestino](const ContaBancaria& c) {
                return c.getNumeroConta() == numeroContaDestino;
            });

        if (itDestino == contas.end()) {
            setColor(12);
            std::cout << "\nConta destino nao encontrada.\n";
            setColor(7);
        } else {
            std::cout << "Valor a transferir: ";
            setColor(14);
            std::cin >> valor;
            setColor(7);

            if (valor <= 0) {
                setColor(12);
                std::cout << "\nValor invalido!\n";
                setColor(7);
            } else if (itOrigem->getSaldo() < valor) {
                setColor(12);
                std::cout << "\nSaldo insuficiente na conta.\n";
                setColor(7);
            } else {
                itOrigem->setSaldo(itOrigem->getSaldo() - valor);
                itDestino->setSaldo(itDestino->getSaldo() + valor);
                persistencia.salvarContasEmArquivo(contas, nomeArquivo);

                setColor(10);
                std::cout << "\nTransferencia realizada com sucesso!" << std::endl;
                std::cout << "Novo saldo da sua conta: " << std::fixed << std::setprecision(2) 
                          << itOrigem->getSaldo() << " Kz\n";
                std::cout << "Novo saldo da conta destino: " << std::fixed << std::setprecision(2) 
                          << itDestino->getSaldo() << " Kz\n";
                setColor(7);
            }
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::realizarPagamento() {
    limparTela();
    setColor(11);
    desenharLinha(50);
    centralizarTexto("PAGAMENTO DE SERVICOS", 50);
    desenharLinha(50);
    setColor(7);

    int numeroConta;
    int opcaoServico;
    double valorPagamento;
    std::string nomeServico;

    std::cout << "\nDigite o numero da sua conta: ";
    setColor(14);
    std::cin >> numeroConta;
    setColor(7);

    auto it = std::find_if(contas.begin(), contas.end(),
        [numeroConta](const ContaBancaria& c) {
            return c.getNumeroConta() == numeroConta;
        });

    if (it == contas.end()) {
        setColor(12);
        std::cout << "\nConta nao encontrada.\n";
        setColor(7);
    } else {
        setColor(14);
        std::cout << "\nServicos disponiveis:\n";
        std::cout << "1. Agua\n";
        std::cout << "2. Luz\n";
        std::cout << "3. Internet\n";
        setColor(7);
        std::cout << "Escolha o servico: ";
        setColor(14);
        std::cin >> opcaoServico;
        setColor(7);

        switch (opcaoServico) {
            case 1: nomeServico = "Agua"; break;
            case 2: nomeServico = "Luz"; break;
            case 3: nomeServico = "Internet"; break;
            default:
                setColor(12);
                std::cout << "\nOpcao invalida!\n";
                setColor(7);
                std::cout << "\nPressione ENTER para continuar...";
                std::cin.ignore();
                std::cin.get();
                return;
        }

        std::cout << "Valor do pagamento: ";
        setColor(14);
        std::cin >> valorPagamento;
        setColor(7);

        if (valorPagamento <= 0) {
            setColor(12);
            std::cout << "\nValor invalido!\n";
            setColor(7);
        } else if (it->getSaldo() < valorPagamento) {
            setColor(12);
            std::cout << "\nSaldo insuficiente!\n";
            setColor(7);
        } else {
            it->setSaldo(it->getSaldo() - valorPagamento);
            persistencia.salvarContasEmArquivo(contas, nomeArquivo);

            setColor(10);
            std::cout << "\nPagamento de " << nomeServico << " realizado com sucesso!" << std::endl;
            std::cout << "Novo saldo: Kz " << std::fixed << std::setprecision(2) << it->getSaldo() << "\n";
            setColor(7);
        }
    }
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}

void Banco::exibirMenu() const {
    limparTela();
    setColor(11);
    desenharLinha(50);
    centralizarTexto("UMABANKING SYSTEM", 50);
    desenharLinha(50);
    setColor(14);
    std::cout << "\n1. Abrir Conta\n";
    std::cout << "2. Depositar\n";
    std::cout << "3. Levantar\n";
    std::cout << "4. Consultar Contas\n";
    std::cout << "5. Transferir\n";
    std::cout << "6. Pagar Servicos\n";
    std::cout << "0. Sair\n";
    setColor(7);
    desenharLinha(50);
    std::cout << "Escolha uma Opcao: ";
}