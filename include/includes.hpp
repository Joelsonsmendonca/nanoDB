// includes.hpp
// Reúne includes padrão utilizados em vários arquivos do projeto.

#pragma once

#include <iostream>   // std::cout, std::endl
#include <vector>     // std::vector usado para chaves e filhos
#include <random>     // geradores aleatórios (std::mt19937, std::random_device)
#include <iomanip>    // formatadores (std::setprecision)
#include <chrono>     // medidas de tempo (benchmark)
#include <algorithm>  // std::shuffle, etc.
#include <numeric>    // std::iota
#include <thread>     // std::this_thread::sleep_for
#include "runner.hpp"  // Inclui runner.hpp para acesso às funções de benchmark e visualização