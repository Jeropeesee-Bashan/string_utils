# string_utils: Yet another strings library for C!

This is a simple C library for working with strings.

- The only dependency is the standard library.
- There currently present such functions as `split_string`, `join_string`,
  `remove_whitespace`, `lstrip_string`, `rstrip_string`, `strip_string`,
  `copy_string`, `next_line`.
- There are no memory allocations until you use `_alloc` tagged functions which
  are kind of convenient.
- `_n` tagged functions require explicit string lengths which is good for extra
  safety and working with certain string views.

## Why?

I wanted to make my own strings library I could trust and rely on so my projects
didn't have any unneccessary external dependencies.

## Project status

The library is currently unstable and unusable yet a few functions can already
be used. There are a lot of tests so you can check if everything works fine.

At the moment this library has both separate header and source files. Since
string_utils is so small, this will be made a single header in the future.
