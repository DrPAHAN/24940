# Getopt Program

A Solaris program that handles various system options using getopt(3C). Implements all required functions with modern GCC features, comprehensive error handling, and modular architecture.

## Compilation

```bash
make
```

or

```bash
gcc -Wall -Wextra -std=c99 -D_GNU_SOURCE -o getopt_program getopt.c
```

## Usage

```bash
./getopt_program [options]
```

## Available Options

- `-i` - Prints real and effective user and group identifiers
- `-s` - Process becomes group leader (uses setpgid(2))
- `-p` - Prints process, parent process, and process group identifiers
- `-u` - Prints ulimit value (file size limit)
- `-U new_ulimit` - Changes ulimit value (uses atol(3C))
- `-c` - Prints core file size limit in bytes
- `-C size` - Changes core file size limit
- `-d` - Prints current working directory
- `-v` - Prints environment variables and their values
- `-V name=value` - Adds new environment variable or changes existing variable value

## Usage Examples

```bash
# Show user and group information
./getopt_program -i

# Show process identifiers
./getopt_program -p

# Show current directory
./getopt_program -d

# Show environment variables
./getopt_program -v

# Set environment variable
./getopt_program -V MYVAR=hello

# Combining options
./getopt_program -i -p -d

# Change ulimit
./getopt_program -U 1000000

# Change core file size
./getopt_program -C 500000

# Complex example
./getopt_program -i -p -d -U 2000000 -V PATH=/usr/local/bin:/usr/bin
```

## Program Architecture

### Modular Structure

The program uses a modular approach with separation of concerns:

- **Argument parsing** - in `main()` function using `getopt(3C)`
- **System operations** - in separate functions for each option
- **Universal functions** - for working with resource limits
- **Helper functions** - for parsing and data processing

### Key Functions

#### Universal functions for limits
```c
void print_rlimit(int resource, const char *description);
void change_rlimit(int resource, const char *value, const char *description);
```

#### Environment variable parsing
```c
int parse_name_value(const char *input, char **name, char **value);
```

#### Environment variable setting
```c
void set_environment_variable(const char *name, const char *value);
```

## Implementation Features

### Error Handling
- **All system calls are checked** for errors
- **Proper memory deallocation** on errors
- **Pointer nullification** after `free()` to prevent dangling pointers
- **Informative error messages** using `perror()`

### Memory Safety
- **Memory allocation checking** for `malloc()` and `strdup()`
- **Safe deallocation** with pointer nullification
- **Memory leak prevention** on errors

### Modularity
- **Separation of parsing and logic** - parsing in main, logic in functions
- **Reusable functions** - universal functions for similar operations
- **Consistent error handling** - uniform approach to error processing

## Technical Details

### Used System Calls
- `getopt(3C)` - command line argument parsing
- `getrlimit(2)` / `setrlimit(2)` - working with resource limits
- `setpgid(2)` - process group management
- `getuid(2)` / `geteuid(2)` / `getgid(2)` / `getegid(2)` - user identifiers
- `getpid(2)` / `getppid(2)` / `getpgrp(2)` - process identifiers
- `getcwd(3)` - getting current directory
- `setenv(3)` - setting environment variables
- `atol(3)` - string to number conversion

### Option Processing
- **Processing order**: right to left (as required in assignment)
- **Multiple options**: one option can appear multiple times
- **Options with parameters**: `-U`, `-C`, `-V` accept mandatory parameters
- **Input validation**: checking value correctness

## Requirements

- **OS**: Solaris system with GCC support
- **Compiler**: GCC with C99 support
- **Libraries**: Standard C libraries (libc)
- **Header files**: 
  - `<unistd.h>` - system calls
  - `<sys/resource.h>` - resource limits
  - `<stdlib.h>` - standard functions
  - `<stdio.h>` - input/output
  - `<string.h>` - string operations

## Build and Installation

```bash
# Compilation
make

# Cleanup
make clean

# Installation (requires root)
make install
```

## GCC Compiler Features

This program is optimized for GCC with the following features:

### Compiler Flags
- **`-Wall`** - Enable all common warnings
- **`-Wextra`** - Enable extra warnings
- **`-std=c99`** - Use C99 standard
- **`-D_GNU_SOURCE`** - Enable GNU extensions

### GCC-Specific Optimizations
- **Built-in `strdup()`** - Uses GCC's optimized string duplication
- **Built-in `setenv()`** - Uses GCC's environment variable handling
- **Enhanced error checking** - GCC's comprehensive warning system
- **Memory safety** - GCC's advanced memory management features

### Benefits of GCC
- **Better error messages** with detailed warnings
- **Modern C99 features** and extensions
- **Optimized performance** with GCC's advanced optimizations
- **Cross-platform compatibility** with GNU toolchain
- **Rich debugging support** with GCC's debugging features

## Debugging

The program outputs detailed error messages:
- **System errors** via `perror()`
- **Validation errors** with problem description
- **Informative messages** about performed operations
- **GCC warnings** for potential issues during compilation
