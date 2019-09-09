
#include "ExprTree.h"
#include "ExprOps.h"
#include <cassert>

// You will want to implement these functions within this file.

using namespace exprtree;

namespace exprtree {


std::optional<int64_t>
evaluate(const ExprTree& tree, const Environment& environment) {
  return {};
}


std::unordered_map<std::string,size_t>
countSymbols(const ExprTree& tree) {
  return {};
}


std::unordered_map<OpCode,size_t>
countOps(const ExprTree& tree) {
  return {};
}


}
