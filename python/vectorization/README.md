# Vectorization

`python`, `vectorization`, `optimization`, `SoA`

## Objective 

I want to observe the performance increase by choosing vector operations over
standard loops. Using a simple problem of determining the mean of `w` elements
at each index in an array of size `N`

## Findings

With the exception of my smallest test case of 10 elements with a window size of
5, every other example yield a significant speed up with numpy's vector
operation.

## Reflection

[Day 1 - 24 Sep] To my understanding there are two benefits of using vectors 
1. Contiguous memory - Element that are operated frequently with one another are
   stored contiguous in memory (spacial locality). This speeds up memory access.
   SoA like.
2. C vs Python - Python ops have a lot more overhead than C (e.g. handling
   dynamic typing), and each operation incurs a cost to call the C api. Whereas,
   in numpy there is one cost of entering C and every operation is handled
within it without having to go through the interpreter.
3. SIMD - numpy is able to take advantage of this with its C inner loops, which
   the python interpreter is unable to.

For my experiement, since arrays are defined with numpy, it is stored as
C-contiguous blocks so point 1 doesn't apply for it. Still cool to see how big
of difference the SIMD and C api call overhead can make.
