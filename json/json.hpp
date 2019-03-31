#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

namespace json
{

  // A context object provides "local" state for
  // an algorithm.
  struct PrintContext
  {
    std::ostream& os;
    int level;
    bool inl;
    bool cont;
  };

  // Represents the set of all JSON values.
  struct Value
  {
    // Ignore me for now.
    virtual ~Value() = default;

    // Returns the size of this value. By
    // default (to save on typing), we return
    // 1 for leaf nodes.
    virtual int size() const { return 1; }

    // Returns the height of the tree.
    virtual int height() const { return 0; }

    // Print the value to the output stream.
    //
    // The level parameter controls how deeply
    // the value should be indented. 
    virtual void print(std::ostream& os, int level, bool inl, bool cont) const = 0;

    // Print the value using the current context.
    virtual void print(PrintContext& cxt) { }

    // Find an object having a key.
    virtual Value* find_key(std::string const&) { return nullptr; }

    // Find an object having a key/value pair.
    virtual Value* find_key_value(std::string const&, std::string const&) { return nullptr; }
  };

  // Represents the value "null".
  struct Null : Value
  {
    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };

  // Represents the values "true" and "false".
  struct Bool : Value
  {
    Bool(bool v) : value(v) { }
    
    void print(std::ostream& os, int level, bool inl, bool cont) const override;

    // Determines whether we are representing
    // true or false.
    bool value;
  };

  // Represents numeric JSON values. The underlying
  // representation is that of a double.
  struct Number : Value
  {
    Number(double v) : value(v) { }

    void print(std::ostream& os, int level, bool inl, bool cont) const override;

    double value;
  };

  // Represents JSON string values of the
  // for "<characters>".
  //
  // Here, we also inherit from std::string
  // in order to reuse its interface and
  // implementation.
  struct String : Value, std::string
  {
    // Inherit string constructors.
    using std::string::string;

    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };

  // Represents a sequence of values 
  // (recursively).
  //
  // Again, we inherit to reuse the interface
  // of vector (and its implementation).
  //
  // NOTE: std::vector<Value*> is a "polymorphic
  // container" -- a container of polymorphic class
  // objects. The dynamic types of objects in the
  // container can vary at runtime.
  struct Array : Value, std::vector<Value*>
  {
    using std::vector<Value*>::vector;

    int size() const override {
      int n = 1;
      for (Value* v : *this)
        n += v->size();
      return n;
    }

    int height() const override {
      Value* v = *std::max_element(begin(), end(),
        [](Value* a, Value* b) {
          return a->height() < b->height();
        });
      return v->height() + 1;
    }

    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };

  // Represents objects.
  //
  // We hash on std::string rather than String (for 
  // ease of correct implementation) and definitely
  // not on String* (which would hash on addresses,
  // not string values).
  struct Object 
    : Value, std::unordered_map<std::string, Value*>
  {
    using std::unordered_map<std::string, Value*>::unordered_map;

    int size() const override {
      int n = 1;
      for (value_type const& kv : *this)
        n += kv.second->size();
      return n;
    }

    int height() const override {
      return 0;
      // int n = std::max_element(begin(), end(),
      //   [](value_type const& a, value_type const& b) {
      //     return a.second->height() < b.second->height();
      //   });
      // return 1 + n;
    }

    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };


  // Functions

  Value* parse(std::string const& str);


  // Returns the size (number of nodes) in the value.
  // Recursively.
  int size(Value const* val);
  
  // Returns the height of the tree.
  int height(Value const* val);


  std::ostream& operator<<(std::ostream& os, Value const& v);

} // namespace json

