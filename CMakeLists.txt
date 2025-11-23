cmake_minimum_required(VERSION 3.10)
project(NanoDB)

set(CMAKE_CXX_STANDARD 20) 

# Onde estão os headers (.hpp)
include_directories(include)

# Cria o executável 'nanoDB' juntando o main e a implementação da BTree
add_executable(nanoDB 
    src/main.cpp 
    src/BTree.cpp
)