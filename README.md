# redmond-cat

# redmond-cat

![CI](https://github.com/polatengin/redmond-cat/actions/workflows/ci.yml/badge.svg)

A minimal, from-scratch reimplementation of the classic Unix `cat` command in C.  
This project was built to learn low-level Linux programming and create a clean, modern `cat` clone without external dependencies.

## Features

- Concatenate files to standard output
- Read from stdin if no files are provided
- Options:
  - `-n` → number all output lines
  - `-s` → squeeze multiple blank lines into one
  - `--help` → show help message
  - `--version` → show version

## Installation

```sh
make
sudo make install
```

This will install:

- Binary: /usr/local/bin/redmond-cat
- Man page: /usr/local/share/man/man1/redmond-cat.1

To uninstall:

```sh
sudo make uninstall
```

## Usage

Concatenate two files:

```sh
redmond-cat file1.txt file2.txt
```

Number all lines:

```sh
redmond-cat -n file.txt
```

Squeeze multiple blank lines:

```sh
redmond-cat -s file.txt
```

Read from stdin:

```sh
echo "Hello world" | redmond-cat
```

Show help:

```sh
redmond-cat --help
```

## Why _POSIX_C_SOURCE?

The macro _POSIX_C_SOURCE 200809L ensures that POSIX-compliant functions (like getline) are visible when compiling with strict standards (-std=c11).
Without it, some compilers may not expose getline, leading to portability issues.
