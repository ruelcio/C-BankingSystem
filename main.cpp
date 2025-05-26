#include <iostream>
#include "banco.hpp"

int main() {
    Banco banco;
    int opcao;

    do {
        banco.exibirMenu();
        std::cin >> opcao;
        std::cin.ignore(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                banco.abrirConta();
                break;
            case 2:
                banco.depositar();
                break;
            case 3:
                banco.realizarLevantamento();
                break;
            case 4:
                banco.listarContas();
                break;
            case 5:
                banco.realizarTransferencia();
                break;
            case 6:
                banco.realizarPagamento();
                break;
            case 0:
                std::cout << "Saindo do sistema...\n";
                break;
            default:
                std::cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);

    return 0;
}
