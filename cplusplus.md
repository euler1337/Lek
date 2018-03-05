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

