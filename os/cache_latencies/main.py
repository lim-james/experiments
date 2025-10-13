import numpy as np
from random import randint
from time import perf_counter_ns

L1D_CACHE_SIZE_BYTES = 65536
L2_CACHE_SIZE_BYTES = 4194304
TOTAL_CACHE_SIZE_BYTES = L1D_CACHE_SIZE_BYTES + L2_CACHE_SIZE_BYTES
INT_64_SIZE = 8

L1_FRIENDLY_CAPACITY = (L1D_CACHE_SIZE_BYTES // INT_64_SIZE) >> 1
L2_FRIENDLY_CAPACITY = TOTAL_CACHE_SIZE_BYTES // INT_64_SIZE
UNFRIENDLY_CAPACITY  = (TOTAL_CACHE_SIZE_BYTES // INT_64_SIZE) << 1


def prime_cache(arr, count):
    for _ in range(count): 
        arr += 1 # sequential access

def random_access(arr, count):
    n = len(arr)-1
    for _ in range(count):
        arr[randint(0, n)] += 1

for t in (L1_FRIENDLY_CAPACITY, L2_FRIENDLY_CAPACITY, UNFRIENDLY_CAPACITY):
    print(f'sample size of {t * INT_64_SIZE}MB')
    arr = np.arange(t, dtype=np.int64)

    start = perf_counter_ns()
    prime_cache(arr, 100)
    end = perf_counter_ns()

    print(f'sequential access took {(end - start) / (100 * t)}ns')

    # random_access_count = 100_000
    # start = perf_counter_ns()
    # random_access(arr, random_access_count)
    # end = perf_counter_ns()

    # print(f'{random_access_count} random access took {(end - start)//random_access_count}ns')
    # print('\n')
