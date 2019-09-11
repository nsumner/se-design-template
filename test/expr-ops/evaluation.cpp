
#include "doctest.h"

#include "ExprTree.h"
#include "ExprOps.h"

using namespace exprtree;


TEST_CASE("empty") {
  Environment env;
  ExprTree tree;

  auto result = evaluate(tree, env);

  CHECK(!result.has_value());
}


TEST_CASE("literal") {
  Environment env;
  ExprTree tree;
  auto three = tree.addLiteral(3);
  tree.setRoot(three);

  auto result = evaluate(tree, env);

  CHECK(result == 3);
}


TEST_CASE("symbol") {
  Environment env;
  env.set("x", 42);

  ExprTree tree;
  auto x = tree.addSymbol("x");
  tree.setRoot(x);

  auto result = evaluate(tree, env);

  CHECK(result == 42);
}


TEST_CASE("addition") {
  Environment env;
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto five = tree.addLiteral(5);
  auto add = tree.addOperation(OpCode::ADD, three, five);
  tree.setRoot(add);

  auto result = evaluate(tree, env);

  CHECK(result == 8);
}


TEST_CASE("subtraction") {
  Environment env;
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto five = tree.addLiteral(5);
  auto subtract = tree.addOperation(OpCode::SUBTRACT, three, five);
  tree.setRoot(subtract);

  auto result = evaluate(tree, env);

  CHECK(result == -2);
}


TEST_CASE("multiplication") {
  Environment env;
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto five = tree.addLiteral(5);
  auto multiply = tree.addOperation(OpCode::MULTIPLY, three, five);
  tree.setRoot(multiply);

  auto result = evaluate(tree, env);

  CHECK(result == 15);
}


TEST_CASE("division") {
  Environment env;
  ExprTree tree;
  auto five = tree.addLiteral(5);
  auto three = tree.addLiteral(3);
  auto divide = tree.addOperation(OpCode::DIVIDE, five, three);
  tree.setRoot(divide);

  auto result = evaluate(tree, env);

  CHECK(result == 1);
}


TEST_CASE("missing symbol") {
  Environment envMissing;
  Environment envFound;
  envFound.set("x", 42);

  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto x = tree.addSymbol("x");
  auto subtract = tree.addOperation(OpCode::SUBTRACT, three, x);
  tree.setRoot(subtract);

  auto resultMissing = evaluate(tree, envMissing);
  auto resultFound = evaluate(tree, envFound);

  // Note, we require both that evaluation when a symbol is not
  // missing to yield a value *and* evaluation when a symbol is
  // missing to not yield a value.
  CHECK(!resultMissing);
  CHECK(resultFound.has_value());
}


TEST_CASE("divide by 0") {
  Environment env;
  ExprTree tree;
  auto five = tree.addLiteral(5);
  auto three = tree.addLiteral(3);
  auto zero = tree.addLiteral(0);
  auto divideBy0 = tree.addOperation(OpCode::DIVIDE, three, zero);
  auto divideBy5 = tree.addOperation(OpCode::DIVIDE, three, five);

  tree.setRoot(divideBy0);
  auto div0Result = evaluate(tree, env);

  tree.setRoot(divideBy5);
  auto div5Result = evaluate(tree, env);

  // Note, we require both that evaluation when a denominator is nonzero
  // to yield a value *and* evaluation when a denominator is nonzero
  // to not yield a value.
  CHECK(!div0Result);
  CHECK(div5Result.has_value());
}


TEST_CASE("Nested left") {
  Environment env;
  ExprTree tree;
  auto two = tree.addLiteral(2);
  auto three = tree.addLiteral(3);
  auto four = tree.addLiteral(4);
  auto five = tree.addLiteral(5);

  auto m1 = tree.addOperation(OpCode::MULTIPLY, two, three);
  auto a1 = tree.addOperation(OpCode::ADD, m1, four);
  auto m2 = tree.addOperation(OpCode::MULTIPLY, a1, five);
  tree.setRoot(m2);

  auto result = evaluate(tree, env);

  CHECK(result == 50);
}


TEST_CASE("Nested right") {
  Environment env;
  ExprTree tree;
  auto two = tree.addLiteral(2);
  auto three = tree.addLiteral(3);
  auto four = tree.addLiteral(4);
  auto five = tree.addLiteral(5);

  auto m1 = tree.addOperation(OpCode::MULTIPLY, two, three);
  auto a1 = tree.addOperation(OpCode::ADD, four, m1);
  auto m2 = tree.addOperation(OpCode::MULTIPLY, five, a1);
  tree.setRoot(m2);

  auto result = evaluate(tree, env);

  CHECK(result == 50);
}


TEST_CASE("Multiple symbols") {
  Environment env;
  env.set("a", 8);
  env.set("b", 13);
  env.set("c", 21);
  env.set("d", 34);

  ExprTree tree;
  auto a = tree.addSymbol("a");
  auto b = tree.addSymbol("b");
  auto c = tree.addSymbol("c");
  auto d = tree.addSymbol("d");

  auto m1 = tree.addOperation(OpCode::MULTIPLY, b, a);
  auto m2 = tree.addOperation(OpCode::MULTIPLY, c, d);
  auto a1 = tree.addOperation(OpCode::ADD, m1, m2);
  tree.setRoot(a1);

  auto result = evaluate(tree, env);

  CHECK(result == 818);
}


TEST_CASE("Literals and symbols") {
  Environment env;
  env.set("a", 8);
  env.set("b", 13);

  ExprTree tree;
  auto a = tree.addSymbol("a");
  auto b = tree.addSymbol("b");
  auto c = tree.addLiteral(21);
  auto d = tree.addLiteral(34);

  auto m1 = tree.addOperation(OpCode::MULTIPLY, b, a);
  auto m2 = tree.addOperation(OpCode::MULTIPLY, c, d);
  auto a1 = tree.addOperation(OpCode::ADD, m1, m2);
  tree.setRoot(a1);

  auto result = evaluate(tree, env);

  CHECK(result == 818);
}

