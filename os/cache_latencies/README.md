# Cache Latencies

## Pre-thoughts

Well with modern systems, memory access becomes our main point of contention for
execution times. How fast we can get our data is then dependent on where it lies
-> L1, L2, L3 or even main mem. I know this but I would also like to see how much
of a difference are we talking about. 

## Setup 

From my previous experiments, I came across `sysctl hw.l1dcachesize` that
informs me of how big my cache size is. The plan here is to have varying sizes
of information - one that is cache friendly, one that exceeds the bounds, and
observe the time difference.

## Thoughts

Attempted with Python with Numpy but even after exceeding memory space the time
difference doesn't seem to vary. Deciding ot move experiement to cpp to have
more expected behaviour. Upon moving to cpp, the numbers became more consistent
and "expected"


```py
>>> 8192 elements
sequential access = 1.5334e-05
random access     = 0.0504366
>>> 524288 elements
sequential access = 0.000997209
random access     = 0.0674987
>>> 1048576 elements
sequential access = 0.00201188
random access     = 0.0618353
>>> 10485760 elements
sequential access = 0.020157
random access     = 0.191863
```
Observed that random access for memory outside of entire cache takes a
significant dip in performance.
