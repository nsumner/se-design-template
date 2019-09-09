
#include "doctest.h"

#include "ExprTree.h"
#include "ExprOps.h"

using namespace exprtree;


TEST_CASE("empty") {
  ExprTree tree;

  auto result = countSymbols(tree);

  CHECK(result.empty());
}


TEST_CASE("literal") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  tree.setRoot(three);

  auto result = countSymbols(tree);

  CHECK(result.empty());
}


TEST_CASE("1x1") {
  ExprTree tree;
  auto x = tree.addSymbol("x");
  tree.setRoot(x);

  auto result = countSymbols(tree);

  CHECK(result.size() == 1);
  CHECK(result["x"] == 1);
}


TEST_CASE("2x1") {
  ExprTree tree;
  auto x = tree.addSymbol("x");
  auto y = tree.addSymbol("y");
  auto add = tree.addOperation(OpCode::ADD, x, y);
  tree.setRoot(add);

  auto result = countSymbols(tree);

  CHECK(result.size() == 2);
  CHECK(result["x"] == 1);
  CHECK(result["y"] == 1);
}


TEST_CASE("nx?") {
  ExprTree tree;
  auto x = tree.addSymbol("x");
  auto y = tree.addSymbol("y");
  auto z = tree.addSymbol("z");
  auto x2 = tree.addOperation(OpCode::MULTIPLY, x, x);
  auto x3 = tree.addOperation(OpCode::MULTIPLY, x2, x);
  auto y2 = tree.addOperation(OpCode::MULTIPLY, y, y);
  auto xy = tree.addOperation(OpCode::ADD, x3, y2);
  auto xyz = tree.addOperation(OpCode::ADD, xy, z);
  tree.setRoot(xyz);

  auto result = countSymbols(tree);

  CHECK(result.size() == 3);
  CHECK(result["x"] == 3);
  CHECK(result["y"] == 2);
  CHECK(result["z"] == 1);
}

