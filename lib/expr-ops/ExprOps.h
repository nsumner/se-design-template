// 64b804de70653b72415b8647897f113a

#pragma once

#include <optional>
#include <string>
#include <unordered_map>

// This file defines the core interface of the functions that you need to define
// for expression trees.

namespace exprtree {


std::optional<int64_t>
evaluate(const ExprTree& tree, const Environment& environment);


std::unordered_map<std::string,size_t>
countSymbols(const ExprTree& tree);


std::unordered_map<OpCode,size_t>
countOps(const ExprTree& tree);


}
