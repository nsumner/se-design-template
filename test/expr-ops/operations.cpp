
#include "doctest.h"

#include "ExprTree.h"
#include "ExprOps.h"

using namespace exprtree;


TEST_CASE("empty") {
  ExprTree tree;

  auto result = countOps(tree);

  CHECK(result.empty());
}


TEST_CASE("literal") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  tree.setRoot(three);

  auto result = countOps(tree);

  CHECK(result.empty());
}


TEST_CASE("addition") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto five = tree.addLiteral(5);
  auto add = tree.addOperation(OpCode::ADD, three, five);
  tree.setRoot(add);

  auto result = countOps(tree);

  CHECK(result.size() == 1);
  CHECK(result[OpCode::ADD] == 1);
}


TEST_CASE("subtraction") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto five = tree.addLiteral(5);
  auto subtract = tree.addOperation(OpCode::SUBTRACT, three, five);
  tree.setRoot(subtract);

  auto result = countOps(tree);

  CHECK(result.size() == 1);
  CHECK(result[OpCode::SUBTRACT] == 1);
}


TEST_CASE("multiplication") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto five = tree.addLiteral(5);
  auto multiply = tree.addOperation(OpCode::MULTIPLY, three, five);
  tree.setRoot(multiply);

  auto result = countOps(tree);

  CHECK(result.size() == 1);
  CHECK(result[OpCode::MULTIPLY] == 1);
}


TEST_CASE("division") {
  ExprTree tree;
  auto five = tree.addLiteral(5);
  auto three = tree.addLiteral(3);
  auto divide = tree.addOperation(OpCode::DIVIDE, five, three);
  tree.setRoot(divide);

  auto result = countOps(tree);

  CHECK(result.size() == 1);
  CHECK(result[OpCode::DIVIDE] == 1);
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

  auto result = countOps(tree);

  CHECK(result.size() == 2);
  CHECK(result[OpCode::MULTIPLY] == 3);
  CHECK(result[OpCode::ADD] == 2);
}

