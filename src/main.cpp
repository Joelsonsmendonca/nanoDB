// main.cpp
// Programa principal que executa um pequeno benchmark da B-Tree implementada
// Explicações estão em português: este ficheiro gera chaves, mede tempo de
// inserção em massa e mede tempo de busca para um valor-alvo.

#include "../include/BTree.hpp"

int main() {
    // --- CONFIGURAÇÃO ---
    // Grau mínimo 't' da B-Tree. Em uma B-Tree real este valor afeta altura vs.
    // tamanho dos nós; aqui usamos um valor alto para reduzir a altura da árvore
    // e demonstrar comportamento em nós maiores.
    int grauMinimo = 50; // Grau alto para simular banco de dados
    int quantidadeDados = 100; // número de registros a inserir
    
    // Cria a BTree com o grau mínimo configurado
    bTree tree(grauMinimo);

    std::cout << "=== NANO DB: B-Tree Engine Benchmark ===\n";
    std::cout << "Grau Minimo (t): " << grauMinimo << "\n";
    std::cout << "Registros a inserir: " << quantidadeDados << "\n\n";

    // 1) Preparação dos dados (fora da medição de tempo)
    // Geramos chaves 0..N-1 e embaralhamos para inserir em ordem aleatória.
    std::cout << "Gerando " << quantidadeDados << " chaves aleatorias..." << std::endl;

    // Cria um vetor contendo 0,1,2,...,quantidadeDados-1
    std::vector<int> chaves(quantidadeDados);
    std::iota(chaves.begin(), chaves.end(), 0);

    // Embaralha as chaves para evitar padrão ordenado (o que influencia
    // fortemente o comportamento da árvore durante inserções)
    std::mt19937 rng(std::random_device{}());
    std::shuffle(chaves.begin(), chaves.end(), rng);

    // 2) Inserção massiva (agora medimos o tempo)
    std::cout << "[2] Iniciando insercao massiva..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    // Insere cada chave na B-Tree. A política atual permite chaves duplicadas;
    // o comportamento resulta em múltiplas entradas idênticas caso existam
    // duplicatas na entrada.
    for (int key : chaves) {
        tree.insert(key);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_insert = end - start;

    std::cout << ">> Insercao concluida em: " << std::fixed << std::setprecision(6)
        << duration_insert.count() << " s.\n\n";

    // 3) Teste de busca (SELECT)
    std::cout << "[3] Testando velocidade de busca (SELECT)..." << std::endl;
    // Valor alvo para busca; dependendo de 'quantidadeDados' provavelmente não
    // estará presente — isso serve para medir o tempo de busca de chave não
    // existente também.
    int alvo = 875321;

    start = std::chrono::high_resolution_clock::now();
    bool achou = tree.search(alvo);
    end = std::chrono::high_resolution_clock::now();

    auto duration_search = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (achou) std::cout << ">> Valor " << alvo << " ENCONTRADO.\n";
    else std::cout << ">> Valor " << alvo << " Não encontrado.\n";

    std::cout << ">> Tempo de busca: " << duration_search.count() << " microssegundos.\n";

    // Imprime a estrutura da árvore (útil para visualização em pequenos testes)
    tree.printTree();

    return 0;
}