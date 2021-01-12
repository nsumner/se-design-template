// 1f3f0cf7a91b9d72bf734d3a2e74a655

#pragma once

#include <deque>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>

namespace exprtree {


class Expression;
class Symbol;
class Literal;
class Operation;


// This class provides the base functionality of an inheritance driven Visitor.
// By sublclassing this, new behaviors can be added to tree expressions without
// modifying the tree expression class and mixing the concerns of the
// expressions and the new behavior.
//
// You should consider the alternatives to inheritance based visitation, as
// discussed in class. What are the trade offs?
//
class ExprVisitor {
public:
  void visit(const Literal& literal)     { visitImpl(literal); }
  void visit(const Symbol& symbol)       { visitImpl(symbol); }
  void visit(const Operation& operation) { visitImpl(operation); }

private:
  virtual void visitImpl(const Literal& literal) { }
  virtual void visitImpl(const Symbol& symbol) { }
  virtual void visitImpl(const Operation& operation) { }
};


// We use an inheritance structure on expressions to support the fact that
// an operation may contain subexpressions of arbitrary form. Note that this
// interacts with the visitor. It becomes harder to control the return type
// when relying on inheritance. Why? What are the possible solutions? Where
// is the complexity pushed?
//
// Consider: This problem is frequently encountered and solved in different
// ways. The way that it is handled in LLVM is quite different from how it is
// solved in Antlr.
//
class Expression {
public:
  virtual void accept(ExprVisitor& visitor) const = 0;
};


// A `Literal` expresses a value that is known ahead of type and represented
// syntactically within an expression. It represents the value with which it
// is initialized.
//
// In 3 * x + 1, 3 and 1 are literals.
//
class Literal final : public Expression {
public:
  explicit Literal(int64_t value)
    : value{value}
      { }

  void accept(ExprVisitor& visitor) const final { return visitor.visit(*this); }

  const int64_t value;
};


// A `Symbol` represents a named value that is not known ahead of time within
// an expression. A binding between a Symbol and the value it represents may
// be provided in an Environment. By looking up the symbol in the environment,
// you can determine what value it should have.
//
// In 3 * x + 1, x in a symbol.
//
class Symbol final : public Expression {
public:
  explicit Symbol(std::string name)
    : name{std::move(name)}
      { }

  void accept(ExprVisitor& visitor) const final { return visitor.visit(*this); }

  const std::string name;
};


enum OpCode : uint8_t {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE
};


// An `Operation` performs some action on two values. Thus, an operation is
// an internal node of the expression tree.
class Operation final : public Expression {
public:
  Operation(OpCode opCode, const Expression& lhs, const Expression& rhs)
    : opCode{opCode},
      lhs{lhs},
      rhs{rhs}
      { }

  void accept(ExprVisitor& visitor) const final { return visitor.visit(*this); }

  const OpCode opCode;
  const Expression& lhs;
  const Expression& rhs;
};


class ExprTree {
public:
  ExprTree()
    : operations{},
      literals{},
      symbols{},
      root{nullptr}
      { }

  void
  accept(ExprVisitor& visitor) const {
    if (root) {
      root->accept(visitor);
    }
  }

  // The builder methods are unsafe in a few ways. Can you think about how
  // you would fix them to be safer?

  [[nodiscard]] const Operation&
  addOperation(OpCode opcode, const Expression& lhs, const Expression& rhs) {
    operations.emplace_back(opcode, lhs, rhs);
    return operations.back();
  }

  [[nodiscard]] const Literal&
  addLiteral(int64_t value) {
    literals.emplace_back(value);
    return literals.back();
  }

  [[nodiscard]] const Symbol&
  addSymbol(std::string name) {
    symbols.emplace_back(std::move(name));
    return symbols.back();
  }

  void
  setRoot(const Expression& expr) {
    root = &expr;
  }

private:
  std::deque<Operation> operations;
  std::deque<Literal> literals;
  std::deque<Symbol> symbols;
  const Expression* root;
};


struct Environment {
public:
  void
  set(const std::string& key, int64_t value) {
    assignments[key] = value;
  }

  [[nodiscard]] std::optional<int64_t>
  get(const std::string& key) const {
    auto found = assignments.find(key);
    if (found != assignments.end()) {
      return {found->second};
    } else {
      return {};
    }
  }

private:
  std::unordered_map<std::string, uint64_t> assignments;
};


}

