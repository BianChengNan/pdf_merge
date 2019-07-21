# Introduction

This is a simple command line utility that lets you combine multiple pdf files into one.

[WIP]

# Building

You will need cmake.

Run the following to build the project (run from top project directory):

```
cmake .
make
```

The executable will be placed inside of the `/bin` directory. Add this to your path if you want to access
it everywhere else.

# Development

Using GoogleTest for unit testing. Tests are written in `pdf_merge` and listed in the `CMakeLists.txt`.

Run tests like so:

```
cmake .
make
ctest
```

To view failure output run `ctest` with a `-V` argument like so: `ctest -V`
