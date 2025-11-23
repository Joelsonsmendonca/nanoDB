#include "../include/BTree.hpp"

int main() {
    // --- CONFIGURAÇÃO ---
    int grauMinimo = 50; // Grau alto para simular banco de dados
    int quantidadeDados = 100; // 100 Milhões de registros
    
    bTree tree(grauMinimo);

    std::cout << "=== NANO DB: B-Tree Engine Benchmark ===\n";
    std::cout << "Grau Minimo (t): " << grauMinimo << "\n";
    std::cout << "Registros a inserir: " << quantidadeDados << "\n\n";

// 1. Preparação dos Dados (Fora do cronômetro)
    std::cout << "Gerando " << quantidadeDados << " chaves aleatorias..." << std::endl;
    
    // Cria um vetor com números de 0 a N
    std::vector<int> chaves(quantidadeDados);
    std::iota(chaves.begin(), chaves.end(), 0); 

    // Embaralha os números (O Caos!)
    std::mt19937 rng(std::random_device{}());
    std::shuffle(chaves.begin(), chaves.end(), rng);

    // 2. Inserção Massiva (Agora sim, valendo!)
    std::cout << "[2] Iniciando insercao massiva..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    for(int key : chaves) {
        tree.insert(key);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration_insert = end - start;
    
    std::cout << ">> Insercao concluida em: " << std::fixed << std::setprecision(6) 
        << duration_insert.count() << " s.\n\n";

    // --- TESTE DE BUSCA ---
    std::cout << "[3] Testando velocidade de busca (SELECT)..." << std::endl;
    int alvo = 875321; // Um valor aleatório no meio
    
    start = std::chrono::high_resolution_clock::now();
    bool achou = tree.search(alvo);
    end = std::chrono::high_resolution_clock::now();
    
    auto duration_search = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (achou) std::cout << ">> Valor " << alvo << " ENCONTRADO.\n";
    else std::cout << ">> Valor " << alvo << " Não encontrado.\n";
    
    std::cout << ">> Tempo de busca: " << duration_search.count() << " microssegundos.\n";

    tree.printTree();
    return 0;
}