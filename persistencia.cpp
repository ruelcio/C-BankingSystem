#include "Persistencia.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Se for necessário, crie setters em ContaBancaria para saldo e IBAN
// ou adapte o construtor para receber saldo e IBAN

void salvarContasEmArquivo(const std::vector<ContaBancaria>& contas, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo para salvar contas.\n";
        return;
    }
    for (const auto& conta : contas) {
        arquivo << conta.getNumeroConta() << ";"
                << conta.getNomeCompleto() << ";"
                << conta.getNumeroBI() << ";"
                << conta.getNacionalidade() << ";"
                << conta.getDataNascimento() << ";"
                << conta.getSaldo() << ";"
                << conta.getIban() << "\n";
    }
}

    void carregarContasDoArquivo(std::vector<ContaBancaria>& contas, const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        // arquivo não existe? só ignora (programa inicia com vetor vazio)
        return;
    }

    contas.clear();
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::istringstream ss(linha);
        std::string token;
        int numeroConta;
        std::string nome, bi, nacionalidade, nascimento, iban;
        double saldo;

        std::getline(ss, token, ';');
        numeroConta = std::stoi(token);

        std::getline(ss, nome, ';');
        std::getline(ss, bi, ';');
        std::getline(ss, nacionalidade, ';');
        std::getline(ss, nascimento, ';');

        std::getline(ss, token, ';');
        saldo = std::stod(token);

        std::getline(ss, iban, ';');

        ContaBancaria conta(numeroConta, nome, bi, nacionalidade, nascimento);
        conta.setSaldo(saldo);  // aqui seta o saldo lido do arquivo
        conta.setIban(iban);    // aqui seta o IBAN lido do arquivo

        contas.push_back(conta);
    }
}
    
