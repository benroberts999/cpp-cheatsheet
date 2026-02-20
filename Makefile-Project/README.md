# Building with Make

This example project uses a **Makefile** to compile C++ code automatically.  
Make tracks which files changed and only recompiles what’s needed, saving time and avoiding mistakes.

## Why use Make?

- **One command build:** compile everything with `make`
- **Automatic dependencies:** if you edit a `.cpp` or `.hpp`, only affected files rebuild
- **Multiple executables:** each `main()` becomes its own program
- **Clean rebuilds:** remove all compiled files with `make clean`

For anything beyond tiny programs, this is much easier than typing compiler commands by hand. For even larger projects, more advanced utilities like CMake exist too.
