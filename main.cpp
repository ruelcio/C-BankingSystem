#include "banco.hpp"
#include <iostream>
#include <limits>

int main() {
    Banco banco("contas.txt");
    int opcao;

    do {
        banco.exibirMenu();
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                std::cout << "\nObrigado por usar o UMABANKING SYSTEM!\n";
                break;
            default:
                std::cout << "\nOpcao invalida!\n";
                std::cout << "Pressione ENTER para continuar...";
                std::cin.get();
        }
    } while (opcao != 0);

    return 0;
}
