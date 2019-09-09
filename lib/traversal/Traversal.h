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
template<class GraphKind>
void
traverse(GraphKind& graph, auto onNode, auto onEdge) {
}


}
