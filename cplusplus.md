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
* The compiler will generate a __destructor__ unless you declare one
