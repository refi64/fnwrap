fnwrap
======

*fnwrap* is a header-only, C++11 library that makes it easy to wrap functions.
For instance, this Python code:

.. code-block:: python

  def myfunc(a, b): # Whatever...

  def wrapper(*args, **kw):
      print('Before myfunc')
      myfunc()
      print('After myfunc')

is equivalent to this code using *fnwrap*:

.. code-block:: c++

  #include "fnwrap.hpp"

  void myfunc(int a, int b) { /* ... */ }

  FNWRAP(myfunc, , wrapper, puts("Before myfunc"), puts("After myfunc"))

Downloading
***********

Just clone and copy *fnwrap.hpp* into your project.

Usage
*****

Using *fnwrap* revolves around the ``FNWRAP`` macro. It's defined like so:

.. code-block:: c++

  #define FNWRAP(original_function, which_overload, new_wrapper_name,
                 code_to_run_before, code_to_run_after)

(Ignore the ``which_overload`` parameter for now.) The parameters
``which_overload``, ``code_to_run_before``, and ``code_to_run_after`` can be
empty.

Example usage:

.. code-block:: c++

  // Creates a function myfunc_wrapper1 that *just* calls myfunc.
  FNWRAP(myfunc, , myfunc_wrapper1, , )
  // Creates a function myfunc_wrapper2 that prints a message, then calls myfunc.
  FNWRAP(myfunc, , myfunc_wrapper2, puts("This is printed before!"), )
  // Creates a function myfunc_wrapper3 that calls myfunc, then prints a message.
  FNWRAP(myfunc, , myfunc_wrapper3, , puts("This is printed after!"))
  // Creates a function myfunc_wrapper4 that prints a message, calls myfunc,
  // and then prints another message.
  FNWRAP(myfunc, , myfunc_wrapper4, puts("This is printed before!"),
         puts("This is printed after!"))

Note that the content of the ``code_to_run_before`` and ``code_to_run_after``
parameters must be a basic expression; more complex code should instead be in
a separate function, e.g. ``void before() { puts("Before!"); }`` and
``FNWRAP(myfunc, , myfunc_wrapper, before(), )``.

You can access the content of the arguments passed to the function using the
variables ``a0`` through ``a9``:

.. code-block:: c++

  int myfunc(int x) { return x; }
  FNWRAP(myfunc, , myfunc_wrapper, printf("myfunc(%d) was called\n", a0), )

If you want to wrap an overloaded function, you must specify which one using
the ``which_overload`` parameter:

.. code-block:: c++

  int overload() { puts("Overload #1"); }
  int overload(int x) { puts("Overload #2"); }

  FNWRAP(overload, int(), overload_wrapper1, puts("Before overload() #1"), )
  FNWRAP(overload, int(int), overload_wrapper2,
         printf("Before overload(%d) #2\n", a0), )

License
*******

*fnwrap* is licensed under the MIT Expat license.
