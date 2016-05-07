## CSCI 2312: Programming Assignment 5 Mini 

_templates, STL, C++11_

* * *


### Synopsis


This program is in the test-driven-development (TDD) style, just like the preceding assignments. 




### Grading

 The test suite for this program has __35__ tests. * You cannot edit the givin files at all. Only your `less_functor.h` and `custom_iterator.h` files will be used.

### Compiler

Your program should run on **GCC 4.9.0** or later, or **Clang 3.3** or later. No other compilers are supported.



### Use of libraries

Unless otherwise specified, you are encouraged to make maximum use of the Standard Library, especially the Standard Template Library (STL).

### Coding style

Familiarize yourself with and start following [coding style guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cppstyle.html). There are others on the Web. Pick one and be consistent. _**Note:** If you stumble on the Google C++ Style Guide, be advised that it has been heavily criticized by many leading C++ programmers. I don't advise you to follow it, especially the more advanced features. This Guide is for entry-level coders at Google who need to be able to work with their legacy code. It is not advisable for new projects and novice programmers._

### References

Operator overloading [guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html). For the implementation of `virtual Piece &operator*(Piece &other)` see the file virtual_operator.cpp, 

A very good [C++ tutorial](http://www.learncpp.com/), including many topics we are covering.

Two websites with C++ Reference, [here](http://en.cppreference.com/w/) and [here](http://www.cplusplus.com/).

### Detailed Instructions

#### I. Implementing and specializing a functor 

##### Introduction

A functor is a function object, an object of a class type which overloads the function operator `operator()`. An functor object can be "called" like a function.

```c++
class F {
  public:
    [return type] operator() ([operator argument list]);
}

int main() {
  F f;
  
  T t = f(4, 5, "string");  // T is the same type as the return type of F::operator()
  
  return 0;
}
```

Naturally, a functor class can be a _class template_:

```c++
template <typename T>
class F {
  public:
    [return type] operator() ([operator argument list]);
}

int main() {
  F<W> f;
  
  T t = f(4, 5, "string");
  
  return 0;
}
```

A template _specialization_ is an implementation of a template for a specific type. This is useful if one or more of the types for which the template will be instantiated require special implementation. A common example is comparing numeric primitives and strings. The template specialization syntax is as follows:

```c++
template <typename T>
class F {
  public:
    void operator() (const T &);
}

template <>
class F<std::string> {
  public:
    void operator() (const std::string &);
}
```

Notice (i) the `template <>` line, and (ii) that the rest of the class declaration is non-template since it has been _specialized_ for the type `std::string`.

##### Requirements

1. Implement a template functor `less` for arbitrary types which overload `operator<`.

2. Specialize the template for C-strings (type `const char *`) and standard strings (type `std::string`).

3. To avoid clashes with the `std` namespace, which implements `less`, you need to wrap your implementation in the namespace `CS2312`.

4. You should not use `std::less`.

5. Write your implementation in file `less_functor.h`.

#### II. Implementing a container iterator

##### Introduction

_Iterators_ are one of the three principal entity categories in the Standard Template Library (STL), along with _containers_ and _algorithms_. They are the glue between containers and algorithms and the key element of _generic programming_. While containers and algorithms perform their operations for arbitrary types and are therefore type-independent, it is the iterators that present a generic facade but have type-dependent implementations. In other words, iterators also present a common interface for generic programming with various types, but their implementations are specific for each type.

From the C++ Reference, _an iterator is any object that, pointing to some element in a range of elements (such as an array or a container), has the ability to iterate through the elements of that range using a set of operators (with at least the increment (++) and dereference (*) operators)_. The STL defines a [hierarchy of iterators](http://www.cplusplus.com/reference/iterator/) with the root iterator being the simplest and most limited and the most derived extending to the functionality to the furthest extent and being the most versatile (and, naturally, _expensive_!). Standard iterators are templates with multiple parameters, among which the most important is `iterator_traits`, a class which defines the particular iterator type's characteristics (or, _traits_). These traits serve to identify the proper iterator type for any necessary operation required by containers and algorithms.

The simplest iterators are implemented as pointers (e.g. the `std::vector` iterator can be a simple pointer to an object of the underlying type), but they can be more complex depending on the underlying data type (e.g. the iterator for a linked list has to be a double pointer to the list node type).

Iterators are _template classes_. They can be derived from the appropriate `std::iterator` or can be standalone.

Iterators are nested classes in their container type, allowing their type to be specified as follows:

```c++
container<Widget> widgets;
container<Widget>::iterator it = widgets.begin();
```

Iterators come in two varieties, `const` and non-`const`. The contant iterator does not allow modification of the container elements, while the non-constant one does. Usually, the two varieties are implemented in one template class which is then parameterized by a constant or non-constant types. This reduces code duplication and the risk for errors.

In this exercise, we have a very simple container, a `fixed_array` and two nested iterators, `iterator` and `const_iterator`, which are just raw pointers to the underlying type of the container element. The implementation is very simple and meant to show you what an iterator looks like and contains, and what operations it supports. Neither the container class nor the nested iterators are derived from the STL ones, so they are standalone. They define the necessary _traits_ themselves, nevertheless conforming to the STL naming conventions and types. The `iterator` and `const_iterator` are implemented separately, duplicating several methods. 

**Note:** The implentation is only _partial_ since there are a number of other necessary methods for full compliance and interoperability with the STL.

##### Requirements

1. You are provided with a class declaration for `fixed_array<T>` and the nested `fixed_array<T>::iterator` and `fixed_array<T>::const_iterator` in the file `custom_iterator.h`. You need to implement the methods for the three classes within the file. You can make the definitions inline since this is a template.

2. The two iterators are of the `forward_iterator` type so you will need to implement only the increment, dereferencing, and comparison operators.

3. You need to implement the subscript operator for the `fixed_array<T>`.

4. You need to implement the list-initialization constructor for the `fixed_array<T>` so that a constant array can be defined as follows:

  ```c++
  const fixed_array<double> darr = { 4.5, 6.7, 8.9 };
  ```

  The iterators defined for `darr` will then be of the constant type.

5. You need to implement the standard `begin()` and `end()` methods/operators which return iterators to the **first** element and the element **AFTER** the last. Take a look at the [C++ Reference](http://en.cppreference.com/w/cpp/iterator/begin) to make sure you understand this context. Notice that these two operators are _overloaded_ to return either constant or non-constant iterators, depending on the container type.

6. Study the tests to see how iterators are used and how simple their interface is for the user once they are implemented.
