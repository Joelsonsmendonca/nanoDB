# nanoDB

nanoDB é um projeto experimental/educacional em C++ que implementa uma estrutura de armazenamento simples (em ram por hora) (usando uma B-Tree). No futuro demonstrará conceitos básicos de banco de dados em baixo nível — indexação, persistência simples e operações de leitura/escrita. O repositório contém o código-fonte, cabeçalhos e um CMakeLists para facilitar a compilação.

## Pré-requisitos

- Compilador C++ compatível (g++/clang++)
- CMake (opcional — recomendado para builds repetíveis)

No Linux (Arch):

```bash
sudo pacman -S cmake
```

## Estrutura do projeto

- `CMakeLists.txt` — configuração do build com CMake
- `include/` — cabeçalhos públicos (ex.: `BTree.hpp`, `includes.hpp`)
- `src/` — implementação em C++ (`BTree.cpp`, `main.cpp`)
- `playground.cpp` — arquivo auxiliar para testes/experimentações
- `build/` — diretório onde os arquivos de build (CMake) podem ser gerados

## Como compilar

Existem duas formas principais descritas abaixo: usando CMake (recomendado) ou compilando diretamente com `g++/clang++`.

### 1) Usando CMake (recomendado)

```bash
# Na raiz do projeto
mkdir -p build
cd build
cmake ..
cmake --build .
```

O executável gerado ficará em `build/` e se chamará `nanoDB` (verifique o nome gerado pelo CMake). Para executar:

```bash
./nanoDB
# ou
./build/nanoDB
```

### 2) Compilação direta com g++/clang (modo rápido)

Se preferir compilar diretamente (útil para testes rápidos):

```bash
g++ -g src/main.cpp src/BTree.cpp -I include -o nanoDB
./nanoDB
ou 
clang++ -g src/main.cpp src/BTree.cpp -I include -o nanoDB
./nanoDB
```

Ajuste os caminhos se houverem mais arquivos fonte.

## Como usar

Basta apenas você mudar os valores do grauMinimo na linha 5 do main.cpp e de quantidadeDados na linha 6
depois rodar 
```bash
./nanoDB
``` 

## Testes

Não há uma suíte de testes automatizada incluída por hora.

## Contribuição

Contribuições são bem-vindas. Siga estes passos básicos:

1. Fork do repositório.
2. Crie uma branch com a sua feature ou correção: `git checkout -b feat/minha-feature`.
3. Faça commits pequenos e descritivos.
4. Abra um Pull Request explicando a motivação e o que foi alterado.

Se for adicionar código novo, favor adicionar testes mínimos e atualizar este `README.md` com instruções específicas.

## Licença

MIT - Faça o que quiser com o codigo

## Contato

Para dúvidas ou sugestões, abra uma issue no repositório ou entre em contato.