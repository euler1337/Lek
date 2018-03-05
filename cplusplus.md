# C++ Explained

## Classes Basic.

``` c++
class Thing {
public:
    Thing();                        // default constructor
    Thing(const Thing&);            // copy constructor
    Thing& operator=(const Thing&); // copy-assign
    ~Thing();                       // destructor
    // C++11:
    Thing(Thing&&);                 // move constructor
    Thing& operator=(Thing&&);      // move-assign
};
```

### Compiler generated member funtions

* The compiler will generate a __default constructor__ unless you declare one.
* The compiler will generate a __copy constructor__ unless you declare one
* The compiler will generate a __copy assignment operator__ unless you declare one.
* The compiler will generate a __destructor__ unless you declare one.
* In c++11, move-functions will be generated if some criterias is fulfiled. Google it.

### Member initialization

Members are initialized as stated in the declaration, if the current constructor does not do otherwise.

``` c++
class Foo {
	public:
	int bar = 3;
	char* ptr = nullptr;
	std::string s ="Hello";
};
```

#### Default constructor

Takes no arguments, returns a totally intitialized new object. 
Good practise to have a complete initialization list for all constructors: 
``` c++
Foo::Foo() : bar(3), ptr(nullptr), s("Hello") {}
```
Default constructor runs when:
* Object is created without arguments.
* Array of objects is created.
* When uninitialized member is created.
* Runs for base class when derived class object is created.

#### Single argument constructor
A constructor taking exactly 1 argument. Can be used for an implicit conversion. This opens up for unintended behaviour. Good practise to mark an single argument constructor with the keyword __explicit__ if the constructor is not intended for implicit conversions. 

#### Copy constructor

Create a new object from an already existing object. If argument is not a reference, we will end up with a legenday infinite recursion.
``` c++
Foo::Foo(const Foo& other)
```
Copy constructor runs when:
* Foo f;
* Foo f2 = f1;
* Foo f2(f2);
* At value calls (not reference calls) -> func(f1), but __not__ func(&f1).

#### Assignment operator

Assign an already existing object to the state of another already existing object. Can never create a new object.
``` c++
Foo& Foo::operator=(const Foo& rhs)
```
#### Destructor

Deletes an existing object. Runs when: 

* The delete keyword is used for an object.
* When an object goes out of scope.

## Class members

### Static members

Kind of global variables, in the scope of a class. Only one instance of the variable, with static lifetime but class visibility. 
``` c++
class Foo{
	private:
	static int bar; //Declaration of static variable
};
int Foo::bar{0}; //Definition of static variable.
```
#### Constant static members

__Inline__, __const__ and __constexpr__ static members can be initialized inside the class definition under some circumstances. Google the get the details.

### Static Methods
A method where __this__ keyword does not exist.

### References as members
Reference members must always be initialized, and can not be null. 
The reference can not either be rebound to another object during the lifetime of an object, which put hard restrictions of the assignment operator for the class. More common is to use pointers or smart pointers instead of reference members, but in some cases it might be useful. 

### Const Methods
Only methods marked as __const__ may be called for const objects of a class. 
``` c++
class Foo{
	private:
	void func() const; // May be called for const instances of the class.
};
```
It is good practice to const declare all functions which does not affect the state of an object. This principle if often called __const-correctness__ and is part of documentation and design.

It is also good practice to declare object arguments as __const reference__ as default. 

### Constexpr
The keyword __constexpr__ is an even stronger const meaning that the value is constant and known at compiletime. 

### Mutable
The keyword __mutable__ override constness. An mutable data member can be assigned even when the object is const.

### Type inference
The keyword __auto__ introduced in c++11 can be used in order to make the compiler to figure out the type from the context. In c++14, __auto__ may also be used to tell the compiler to figure out the return type from a function.

## Inheritance
Terminology: Base/Derived-class. 

### Constructors/Destructors

The following functions are not inherited in the derived class:
* Constructors
* Destructors
* Assignment operators

However, the compiler generated ones will call the base class corresponding ones. If a custom one is provided in the derived class, do not forget to call the base class corresponding one, i.e.

``` c++
MyDerived::MyDerived(int a, double b) : 
	MyBase(a), my_extended_member{b} {}
```

It is considered bad practise to access members of base class directly in the derived class constructor. Every class should deal with its own initialization.

### Overriding vs Overloading

* Overriding is to override a method from the base class in the derived class.
* Overloading is the idea to have several functions with the same name but different signatures.

Overriding will hide all functions in the base class with the same name. To make them visible, use the following syntax:

``` c++
class MyBase {
public:
	void func();
	void func(int);
	void func(int, int);	
};
class MyDerived : public MyBase {
public:
using MyBase::func; // Will un-hide all versions of hide in base.
	void func(int);	
};
```
### Base class access
Inherited members visibility and acess is determined by:

``` c++
class MyDerived : public MyBase {};    // Same visibility as in Base
class MyDerived : protected MyBase {}; // Public becomes protected
class MyDerived : private MyBase   {}; // Public & protected becomes private
```

### Multiple inheritance
To derive a class from multiple base classes. All members from all classes are inherited. 

``` c++
class C : public A, public B {};
```
Base classes may be derived from the same class, and one can end up in a scenario where a derived class have multiple instances of a base-class. This could led to the __diamond problem__, where the derived class do not know which method in base-classes to call. This can be solved by __virtual inheritence__: 
``` c++
class A : public virtual X { … }
class B : public virtual X { … }
class MultiDerived : public A, public B { … }
```
Using virtual inheritence, only one instance of the base-base class X is in the derived MultiDerived. It is considered good pratice to prepare class (A,B) for this scenario using virtual inheritence.

### Virtual functions
Used in the common scenario when the pointer and the object is not of the same type. Should the pointer or object type method be called in such a scenario?

* Non-virtual method: static/early bindings -> Pointer type method is called.
* Virtual method: dynamic/late bindings -> Object type method is called.
``` c++
virtual void MyMethod();
```
Keywords __override__ and __final__ could be used to ensure consistency in the code at compile-time, i.e. to guarantee that a base-class function is virtual (or not). This is considered good practice to use.

### Abstract classes
An object of an abstract class can not be created. A class is abstract is at least one of its method is pure virtual: 
``` c++
virtual void MyMethod() = 0; //Pure virtual method
```
Objects deriving from an abstract class must implement all pure virtual methods in the abstract class. Pure virtual methods can also be accesed by pointers to the abstract class.

## Templates

### Function templates
Function templates could be used to implement a single function valid for different datatypes. For example:
``` c++
template <typename T>
T min(T a, T b) 
{
  return (a < b ? a : b);
}
```
A function template is instantiated at compile time. 
``` c++
x = min(2, 17);
x = min('p', 'a'); 
```
Every instantation is a new function! All definitions will be inline and hence the template code must be in the headerfile.

### Class templates
Class templates could be used to implement a class for an arbitrary datatype. For example: 
``` c++
template <typename T> 
class stack {
  T* stk; 
  ...
  void push(T x);
};
```
A class template must be explicitly instantiated: 
``` c++
stack<int> s{};
```

### Value parameters
A value parameter for a template is parameter which is not a datatype but a value. For example, the stack class could use a __size__ value parameter. __Note__ Each unique instantiation will create a new class (not class instance). Hence, compile-time could increase rapidly if value parameters is used without care. 










