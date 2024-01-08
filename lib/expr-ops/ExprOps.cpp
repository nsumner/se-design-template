// 64b804de70653b72415b8647897f113a

#include "ExprTree.h"
#include "ExprOps.h"
#include <cassert>

// You will want to implement these functions within this file.

using exprtree::Environment;
using exprtree::ExprVisitor;
using exprtree::Expression;
using exprtree::Literal;
using exprtree::Operation;
using exprtree::OpCode;
using exprtree::Symbol;

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
