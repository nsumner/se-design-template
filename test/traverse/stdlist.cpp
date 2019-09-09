
#include "doctest.h"

#include <list>
#include <iostream>

#include "Traversal.h"

using namespace traversal;


TEST_CASE("empty") {
  std::list<int> numbers = {};
  std::list<std::pair<int, int>> edges = {};

  std::list<int> foundNodes;
  std::list<std::pair<int, int>> foundEdges;
  auto onNode = [&foundNodes] (auto node) {
    foundNodes.push_back(*node);
  };
  auto onEdge = [&foundEdges] (auto predecessor, auto successor) {
    foundEdges.push_back({*predecessor, *successor});
  };

  traverse(numbers, onNode, onEdge);

  CHECK(numbers == foundNodes);
  CHECK(edges.empty());
}


TEST_CASE("one node") {
  std::list<int> numbers = { 5 };
  std::list<std::pair<int, int>> edges = {};

  std::list<int> foundNodes;
  std::list<std::pair<int, int>> foundEdges;
  auto onNode = [&foundNodes] (auto node) {
    foundNodes.push_back(*node);
  };
  auto onEdge = [&foundEdges] (auto predecessor, auto successor) {
    foundEdges.push_back({*predecessor, *successor});
  };

  traverse(numbers, onNode, onEdge);

  CHECK(numbers == foundNodes);
  CHECK(edges.empty());
}


TEST_CASE("several nodes") {
  std::list<int> numbers = { 5, 3, 7, 1, 9};
  std::list<std::pair<int, int>> edges = {{5,3}, {3,7}, {7,1}, {1,9}};

  std::list<int> foundNodes;
  std::list<std::pair<int, int>> foundEdges;
  auto onNode = [&foundNodes] (auto node) {
    foundNodes.push_back(*node);
  };
  auto onEdge = [&foundEdges] (auto predecessor, auto successor) {
    foundEdges.push_back({*predecessor, *successor});
  };

  traverse(numbers, onNode, onEdge);

  CHECK(numbers == foundNodes);
  CHECK(edges == foundEdges);
}


TEST_CASE("string nodes") {
  std::list<std::string> strings = { "I'm", "sorry", "Dave"};
  std::list<std::pair<std::string, std::string>> edges = {{"I'm", "sorry"}, {"sorry", "Dave"}};

  std::list<std::string> foundNodes;
  std::list<std::pair<std::string, std::string>> foundEdges;
  auto onNode = [&foundNodes] (auto node) {
    foundNodes.push_back(*node);
  };
  auto onEdge = [&foundEdges] (auto predecessor, auto successor) {
    foundEdges.push_back({*predecessor, *successor});
  };

  traverse(strings, onNode, onEdge);

  CHECK(strings == foundNodes);
  CHECK(edges == foundEdges);
}

