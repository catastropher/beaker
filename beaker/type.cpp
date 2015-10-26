// Copyright (c) 2015 Andrew Sutton
// All rights reserved

#include "type.hpp"
#include "decl.hpp"
#include "less.hpp"

#include <set>


template<typename T>
struct Type_less
{
  bool operator()(T const& a, T const& b) const
  {
    return is_less(&a, &b);
  }
};


template<typename T>
using Type_set = std::set<T, Type_less<T>>;


Type const*
get_boolean_type()
{
  static Boolean_type t;
  return &t;
}


Type const*
get_integer_type()
{
  static Integer_type t;
  return &t;
}


Type const*
get_function_type(Type_seq const& t, Type const* r)
{
  static Type_set<Function_type> fn;
  auto ins = fn.emplace(t, r);
  return &*ins.first;
}


Type const*
get_function_type(Decl_seq const& d, Type const* r)
{
  Type_seq t;
  t.reserve(d.size());
  for (Decl* d1 : d)
    t.push_back(d1->type());
  return get_function_type(t, r);
}
