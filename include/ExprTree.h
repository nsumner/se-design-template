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
// when relying on inheritance? Why? What are the possible solutions? Where
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


class Literal : public Expression {
public:
  Literal(int64_t value)
    : value{value}
      { }

  virtual void accept(ExprVisitor& visitor) const { return visitor.visit(*this); }

  const int64_t value;
};


class Symbol : public Expression {
public:
  Symbol(std::string name)
    : name{name}
      { }

  virtual void accept(ExprVisitor& visitor) const { return visitor.visit(*this); }

  const std::string name;
};


enum OpCode : uint8_t {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE
};


class Operation : public Expression {
public:
  Operation(OpCode opCode, const Expression& lhs, const Expression& rhs)
    : opCode{opCode},
      lhs{lhs},
      rhs{rhs}
      { }

  virtual void accept(ExprVisitor& visitor) const { return visitor.visit(*this); }

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

  const Operation&
  addOperation(OpCode opcode, const Expression& lhs, const Expression& rhs) {
    operations.emplace_back(opcode, lhs, rhs);
    return operations.back();
  }

  const Literal&
  addLiteral(int64_t value) {
    literals.emplace_back(value);
    return literals.back();
  }

  const Symbol&
  addSymbol(std::string name) {
    symbols.emplace_back(std::move(name));
    return symbols.back();
  }

  void
  setRoot(Expression& expr) {
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
  set(std::string key, int64_t value) {
    assignments[key] = value;
  }

  std::optional<int64_t>
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

