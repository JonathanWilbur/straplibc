# nolibc, but buildable by TinyCC et al.

This is a version of `nolibc` that can be built using TinyCC, and possibly
other small C compilers / toolchains, such as ChibiCC.

## Background

`nolibc` is a hyper-minimal C standard library that ships with the Linux
kernel source, in `tools/include/nolibc`. While it is nice, it does not build
with any C toolchain except GCC (maybe clang would work; I haven't tried).

This repo is a version of `nolibc` that was slightly modified to be buildable
using other C compilers by using simpler syntax, and using
[`libsyscall`](https://github.com/JonathanWilbur/libsyscall) to make system
calls.

## Limitations

This will only work on x86-64 for now, but I will accept pull requests to add
support for other ISAs.

## Modifications

- `arch.h` was modified to only use x86-64.
- `arch-x86_64.h` was modified to use `libsyscall` and remove
  `__builtin_unreachable`.

## License

Pursuant to the license agreement, the exact text of the MIT license from the
Linux kernel is retained in `licenses/MIT.txt`. This appears to be a template
file and you are supposed to fill in the license values with the values at the
tops of source files. I have retained the license comments and copyright
notices at the tops of the source files that were copied from the Linux repo.

This project chooses the MIT license between the two licensing choices given.
All code written by Jonathan M. Wilbur in this repo is hereby licensed under
an MIT license, with the license being `LICENSE.txt`.

