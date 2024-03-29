// 64b804de70653b72415b8647897f113a

#pragma once

#include <iostream>
#include <optional>
#include <unordered_set>
#include <vector>

#include "ExprTree.h"

namespace traversal {


// You will want to define enough constructs in this header to make it so that
// the traverse function works when passed either a std::list or an ExprTree.
// You *could* add other constructs.


// You should feel free to add template arguments if you want to, but the
// invocations in the test suite should remain valid.
template<class GraphKind, class OnNode, class OnEdge>
void
traverse(GraphKind& graph, OnNode onNode, OnEdge onEdge) {
}


}

