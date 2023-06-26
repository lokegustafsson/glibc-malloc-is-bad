# (your) glibc grows non-main-thread heaps by 4K at a time

This means that doing many small allocations on threads other than the main
thread is way way slower than it ~~could~~ should be. If you do `malloc(256)` in
a loop, every 16th call will perform the `mprotect()` syscall on a 4K page. So
every malloc does 1/16 of a syscall. That's not great.

This shows itself in timings such as this one (3 worker threads allocating a
bunch):
```
real    0m1.468s
user    0m0.531s
sys     0m2.817s
```

You can check whether this also holds on your libc by running `nix develop -c
make` from a checkout of this repo.

(this is true as of glibc 2.37 released Febuary 1st 2023)

One workaround is to use jemalloc.
