#include "runner.hpp"


void runVectorBenchmark(const std::vector<int>& dados, int alvo) {
    std::cout << "\n--------------------------------------------------\n";
    std::cout << "--- BENCHMARK: STD::VECTOR (Lista Simples) ---\n";
    std::cout << "--------------------------------------------------\n";
    
    std::vector<int> vec;
    vec.reserve(dados.size()); // Dando uma chance justa pro vetor reservando memória

    // 1. Inserção
    std::cout << "[Vector] Inserindo " << dados.size() << " elementos...\n";
    auto start = std::chrono::high_resolution_clock::now();
    
    for(int x : dados) {
        vec.push_back(x);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << ">> Vector Insert: " << std::fixed << std::setprecision(6) 
              << elapsed.count() << " s. (Geralmente rapido)\n";

    // 2. Busca Linear (Onde o filho chora e a mãe não vê)
    std::cout << "[Vector] Buscando o valor " << alvo << "...\n";
    start = std::chrono::high_resolution_clock::now();
    
    // std::find faz uma busca linear (O(n)) - percorre um por um
    auto it = std::find(vec.begin(), vec.end(), alvo); 
    
    end = std::chrono::high_resolution_clock::now();
    
    auto duration_search = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    if (it != vec.end()) std::cout << ">> Valor ENCONTRADO.\n";
    else std::cout << ">> Valor NAO encontrado.\n";

    std::cout << ">> Tempo de busca Vector: " << duration_search.count() << " microssegundos.\n";
}

void runBenchmark(int grauMinimo, int quantidadeDados) {
    bTree tree(grauMinimo);

    std::cout << "=== NANO DB: B-Tree Engine Benchmark ===\n";
    std::cout << "Grau Minimo (t): " << grauMinimo << "\n";
    std::cout << "Registros a inserir: " << quantidadeDados << "\n\n";

    // Preparação: vetor de chaves embaralhado
    std::vector<int> chaves(quantidadeDados);
    std::iota(chaves.begin(), chaves.end(), 0);
    std::mt19937 rng(std::random_device{}());
    std::shuffle(chaves.begin(), chaves.end(), rng);

    // Inserção massiva com medição de tempo
    std::cout << "[1] Inserindo chaves...\n";
    auto start = std::chrono::high_resolution_clock::now();
    for (int key : chaves) tree.insert(key);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration_insert = end - start;
    std::cout << ">> Insercao concluida em: " << std::fixed << std::setprecision(6)
              << duration_insert.count() << " s.\n\n";

    // Teste de busca
    std::cout << "[2] Testando busca (SELECT)...\n";
    int alvo = chaves[rng() % quantidadeDados]; // pega uma chave existente aleatória
    start = std::chrono::high_resolution_clock::now();
    bool achou = tree.search(alvo);
    end = std::chrono::high_resolution_clock::now();
    auto duration_search = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (achou) std::cout << ">> Valor " << alvo << " ENCONTRADO.\n";
    else std::cout << ">> Valor " << alvo << " NAO encontrado.\n";

    std::cout << ">> Tempo de busca: " << duration_search.count() << " microssegundos.\n";

    runVectorBenchmark(chaves, alvo);
}

void runVisualization(int grauMinimo) {
    bTree tree(grauMinimo);

    std::cout << "=== NANO DB: Visualizacao da B-Tree ===\n";
    std::cout << "Grau Minimo (t): " << grauMinimo << "\n";

    // Gerar algumas chaves para visualizar
    int quantidade = 15; // só algumas chaves para facilitar a visualizacao
    std::vector<int> chaves(quantidade);
    std::iota(chaves.begin(), chaves.end(), 1);

    // Embaralha para simular inserção aleatória
    std::mt19937 rng(std::random_device{}());
    std::shuffle(chaves.begin(), chaves.end(), rng);

    // Inserção passo a passo com printTree
    for (int i = 0; i < quantidade; i++) {
        std::cout << "\nInserindo chave: " << chaves[i] << "\n";
        tree.insert(chaves[i]);
        std::cout << "Estado atual da B-Tree:\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // pausa para visualização
        tree.printTree();
        std::cout << "-----------------------------\n";
    }
}
