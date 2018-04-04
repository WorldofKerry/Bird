# ROOT

ROOT is a C++ Toolkit for High Energy Physics. It is huge. There are really a lot of ways to use it in CMake, though many/most of the examples you'll find are probably wrong. Here's my recommendation.


## Finding ROOT

ROOT supports config file discovery, so you can just do:

[import:'find_package', lang:'cmake'](../../examples/root-simple/CMakeLists.txt)

to attempt to find ROOT. If you don't have your paths set up, you can pass `-DROOT_DIR=$ROOTSYS/cmake` to find ROOT. (But, really, you should source `thisroot.sh`)

## The wrong way

ROOT provides a utility to set up a ROOT project, which you can activate using `include(${ROOT_USE_FILE})`. This will automatically make ugly global variables for you. It will save you a little time setting up, and will waste massive amounts of time later when you try to do anything more complicated.  Don't use it.

## The right way (Targets)

ROOT does not correctly set up it's imported targets. To fix this error, you'll need something like:

[import:'setup_properties', lang:'cmake'](../../examples/root-simple/CMakeLists.txt)

In CMake 3.11, you can replace that last function call with:


[import:'modern_fix', lang:'cmake'](../../examples/root-simple-3.11/CMakeLists.txt)

All the ROOT targets will require `ROOT::Core`, so this will be enough regardless of which ROOT targets you need.

To link, just pick the libraries you want to use:

[import:'add_and_link', lang:'cmake'](../../examples/root-simple/CMakeLists.txt)

## Dictionary generation

Dictionary generation is ROOT's way of working around the missing reflection feature in C++. It allows ROOT to learn the details of your class so it can save it, show methods in the Cling interpreter, etc. You'll need three things in your source code to make it work for classes:

* Your class definition should end with `ClassDef(MyClassName, 1)`
* Your class implementation should have `ClassImp(MyClassName)` in it
* You should have a file with a name that ends with `LinkDef.h`

The `LinkDef.h` file follows a [specific formula][linkdef-root] and tells ROOT what parts to generate dictionaries for.

To generate, you should include the following in your CMakeLists:

```cmake
include("${ROOT_DIR}/modules/RootNewMacros.cmake")
include_directories(ROOT_BUG)
```

The second line is due to a bug in the NewMacros file that causes dictionary generation to fail if there is not at least one global include directory or a `inc` folder. Here I'm including a non-existent directory just to make it work. There is no `ROOT_BUG` directory.

To generate a file:

```cmake
root_generate_dictionary(G__Example Example.h LINKDEF ExampleLinkDef.h)
```

The final argument, listed after `LINKDEF`, must have a name that ends in `LinkDef.h`. This command will create three files. If you started output name with `G__`, that will be removed from the name, otherwise it will use the name given; this must match the final output library name you will soon be creating. Assuming this is `${NAME}`:

* `${NAME}.cxx`: This file should be included in your sources when you make the library.
* `lib{NAME}.rootmap` (`G__` prefix removed): The rootmap file in plain text
* `lib{NAME}_rdict.pcm` (`G__` prefix removed): A ROOT file

The final two output files must sit next to the library output. This is done by checking `CMAKE_LIBRARY_OUTPUT_DIRECTORY` (it will not pick up local target settings). If you have a libdir set but you don't have (global) install locations set, you'll also need to set `ARG_NOINSTALL` to `TRUE`. 

[linkdef-root]: https://root.cern.ch/selecting-dictionary-entries-linkdefh
