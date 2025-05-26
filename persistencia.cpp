#include "persistencia.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

// Se for necessário, crie setters em ContaBancaria para saldo e IBAN
// ou adapte o construtor para receber saldo e IBAN

void Persistencia::salvarContasEmArquivo(const std::vector<ContaBancaria>& contas, const std::string& nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir arquivo para escrita: " << nomeArquivo << std::endl;
        return;
    }

    for (const auto& conta : contas) {
        arquivo << conta.getNumeroConta() << ";"
                << conta.getNomeCompleto() << ";"
                << conta.getNumeroBI() << ";"
                << conta.getNacionalidade() << ";"
                << conta.getDataNascimento() << ";"
                << std::fixed << std::setprecision(2) << conta.getSaldo() << ";"
                << "AO" << std::setfill('0') << std::setw(10) << conta.getNumeroConta() << "\n";
    }

    arquivo.close();
}

std::vector<ContaBancaria> Persistencia::carregarContas(const std::string& nomeArquivo) {
    std::vector<ContaBancaria> contas;
    std::ifstream arquivo(nomeArquivo);
    
    if (!arquivo.is_open()) {
        std::cerr << "Arquivo nao encontrado: " << nomeArquivo << std::endl;
        return contas;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        try {
            // Primeiro, vamos normalizar a linha substituindo vírgulas por ponto e vírgula
            std::string linhaNormalizada = linha;
            for (char& c : linhaNormalizada) {
                if (c == ',') c = ';';
            }

            std::istringstream iss(linhaNormalizada);
            std::string token;
            
            // Número da conta
            std::getline(iss, token, ';');
            if (token.empty()) continue;
            int numeroConta = std::stoi(token);
            
            // Nome completo
            std::getline(iss, token, ';');
            if (token.empty()) continue;
            std::string nome = token;
            
            // Número do BI
            std::getline(iss, token, ';');
            if (token.empty()) continue;
            std::string bi = token;
            
            // Nacionalidade
            std::getline(iss, token, ';');
            if (token.empty()) continue;
            std::string nacionalidade = token;
            
            // Data de nascimento
            std::getline(iss, token, ';');
            if (token.empty()) continue;
            std::string nascimento = token;
            
            // Saldo
            std::getline(iss, token, ';');
            double saldo = 0.0;
            if (!token.empty()) {
                try {
                    saldo = std::stod(token);
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao converter saldo para conta " << numeroConta << ": " << e.what() << std::endl;
                }
            }
            
            // Criar a conta
            ContaBancaria conta(numeroConta, nome, bi, nacionalidade, nascimento);
            conta.setSaldo(saldo);
            contas.push_back(conta);
            
        } catch (const std::exception& e) {
            std::cerr << "Erro ao processar linha: " << linha << "\nErro: " << e.what() << std::endl;
            continue;
        }
    }

    arquivo.close();
    return contas;
}
    
