
#include "doctest.h"

#include <list>
#include <iostream>
#include <sstream>
#include <variant>

#include "Traversal.h"

using traversal::traverse;

using exprtree::ExprTree;
using exprtree::Expression;
using exprtree::Environment;
using exprtree::OpCode;

using NodeType = const Expression*;
using NodeList = std::vector<NodeType>;
using EdgeList = std::vector<std::pair<NodeType,NodeType>>;


namespace doctest {

template <typename T, template <typename...> typename C>
struct StringMaker<C<std::pair<T,T>>> {
  static String convert(const C<std::pair<T,T>>& edges) {
    std::ostringstream os;
    const char* delimiter = "";
    os << "[";
    for (const auto& edge : edges) {
      os << delimiter << "(" << edge.first << "," << edge.second << ") ";
      delimiter = ", ";
    }
    os << "]";
    return os.str().c_str();
  }
};

template <typename T, template<typename...> typename C>
struct StringMaker<C<T>> {
  static String convert(const C<T>& nodes) {
    std::ostringstream os;
    const char* delimiter = "";
    os << "[";
    for (const auto& node : nodes) {
      os << delimiter << ' ' << node << ' ';
      delimiter = ", ";
    }
    os << "]";
    return os.str().c_str();
  }
};

}


static std::pair<NodeList,EdgeList>
recordTraversal(ExprTree& tree) {
  std::pair<NodeList,EdgeList> results;
  auto onNode = [&results] (auto* node) {
    results.first.push_back(node);
  };
  auto onEdge = [&results] (auto* predecessor, auto* successor) {
    results.second.push_back({predecessor, successor});
  };

  traverse(tree, onNode, onEdge);

  return results;
}


TEST_CASE("empty") {
  ExprTree tree;

  NodeList nodes = { };
  EdgeList edges = { };

  auto [foundNodes, foundEdges] = recordTraversal(tree);

  CHECK(nodes == foundNodes);
  CHECK(edges == foundEdges);
}


TEST_CASE("One node") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  tree.setRoot(three);

  NodeList nodes = { &three };
  EdgeList edges = { };

  auto [foundNodes, foundEdges] = recordTraversal(tree);

  CHECK(nodes == foundNodes);
  CHECK(edges == foundEdges);
}


TEST_CASE("addition nodes") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto x = tree.addSymbol("x");
  auto add = tree.addOperation(OpCode::ADD, three, x);
  tree.setRoot(add);

  NodeList nodes = { &add, &three, &x };

  auto [foundNodes, _] = recordTraversal(tree);
  (void)_;

  CHECK(nodes == foundNodes);
}


TEST_CASE("addition edges") {
  ExprTree tree;
  auto three = tree.addLiteral(3);
  auto x = tree.addSymbol("x");
  auto add = tree.addOperation(OpCode::ADD, three, x);
  tree.setRoot(add);

  EdgeList edges = { {&add,&three}, {&add,&x} };

  auto [_, foundEdges] = recordTraversal(tree);
  (void)_;

  CHECK(edges == foundEdges);
}


TEST_CASE("Literals and symbols nodes") {
  ExprTree tree;
  auto a = tree.addSymbol("a");
  auto b = tree.addSymbol("b");
  auto c = tree.addLiteral(21);
  auto d = tree.addLiteral(34);

  auto m1 = tree.addOperation(OpCode::MULTIPLY, b, a);
  auto m2 = tree.addOperation(OpCode::MULTIPLY, c, d);
  auto a1 = tree.addOperation(OpCode::ADD, m1, m2);
  tree.setRoot(a1);

  NodeList nodes = {&a1, &m1, &b, &a, &m2, &c, &d};

  auto [foundNodes, _] = recordTraversal(tree);
  (void)_;

  CHECK(nodes == foundNodes);
}


TEST_CASE("Literals and symbols edges") {
  ExprTree tree;
  auto a = tree.addSymbol("a");
  auto b = tree.addSymbol("b");
  auto c = tree.addLiteral(21);
  auto d = tree.addLiteral(34);

  auto m1 = tree.addOperation(OpCode::MULTIPLY, b, a);
  auto m2 = tree.addOperation(OpCode::MULTIPLY, c, d);
  auto a1 = tree.addOperation(OpCode::ADD, m1, m2);
  tree.setRoot(a1);

  EdgeList edges = {
    {&a1, &m1},
    {&m1, &b},
    {&m1, &a},
    {&a1, &m2},
    {&m2, &c},
    {&m2, &d},
  };

  auto [_, foundEdges] = recordTraversal(tree);
  (void)_;

  CHECK(edges == foundEdges);
}


TEST_CASE("Tree with reuse") {
  ExprTree tree;
  auto a = tree.addSymbol("a");
  auto b = tree.addSymbol("b");

  auto m1 = tree.addOperation(OpCode::MULTIPLY, b, a);
  auto a1 = tree.addOperation(OpCode::ADD, m1, m1);
  tree.setRoot(a1);

  NodeList nodes = {&a1, &m1, &b, &a};
  EdgeList edges = {
    {&a1, &m1},
    {&m1, &b},
    {&m1, &a},
    {&a1, &m1},  
  };

  auto [foundNodes, foundEdges] = recordTraversal(tree);

  CHECK(nodes == foundNodes);
  CHECK(edges == foundEdges);
}

