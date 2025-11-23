// main.cpp
// Programa principal que executa um pequeno benchmark da B-Tree implementada
// Explicações estão em português: este ficheiro gera chaves, mede tempo de
// inserção em massa e mede tempo de busca para um valor-alvo.

#include "includes.hpp"

int main() {
    int escolha;
    std::cout << "Escolha o modo:\n1 - Benchmark\n2 - Visualizacao\n";
    std::cin >> escolha;

    if (escolha == 1) {
        int quantidadeDados;
        std::cout << "Informe a quantidade de registros para o benchmark: ";
        std::cin >> quantidadeDados;
        runBenchmark(50, quantidadeDados);
    } else if (escolha == 2) {
        runVisualization(3); // Grau menor para visualização
    } else {
        std::cout << "Opcao invalida.\n";
    }
}