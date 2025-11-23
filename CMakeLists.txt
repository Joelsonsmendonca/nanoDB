cmake_minimum_required(VERSION 3.10)
project(NanoDB)

# Define o padrão C++ usado pelo projeto (C++20)
set(CMAKE_CXX_STANDARD 20)

# Diretório onde estão os headers (.hpp). Isso adiciona 'include' ao include path
include_directories(include)

# Cria o executável 'nanoDB' juntando o main e a implementação da BTree
add_executable(nanoDB
    src/main.cpp
    src/BTree.cpp
)

# Observações:
# - O arquivo 'playground.cpp' não está incluído aqui; caso queira compilar o
#   playground como executável separado, faça:
#   clang++ playground.cpp src/BTree.cpp -o playground