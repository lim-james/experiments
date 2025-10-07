from sys import getsizeof 
from time import time
from random import random
from psutil import Process

N = 3_000_000

"""
not inefficient enough 
"""
def fib(x):
    if x in (0,1):
        return 1

    dp = [0] * x
    dp[0:2] = [1,1]
    
    for i in range(2, x):
        dp[i] = dp[i-1] + dp[i-2]

    return dp[-1]


def stress(access_range, array):
    for _ in range(N):
        i = int(random() * access_range)
        #fib(big_array[i])
        big_array[i] = big_array[i] * 2


l1d_cache_size_bytes = 65536
l2_cache_size_bytes  = 4194304
cache_size_bytes     = l1d_cache_size_bytes + l2_cache_size_bytes
integer_size_bytes = 8 #getsizeof(0)

l1_cache_entries = l1d_cache_size_bytes // integer_size_bytes
l2_cache_entries = l2_cache_size_bytes // integer_size_bytes
max_cache_entries = cache_size_bytes // integer_size_bytes

n = int(max_cache_entries * 1.5)
big_array = list(range(n))
flush = list(range(n))

print(f'populating {n} elements')

p = Process()

access_range = l1_cache_entries >> 1
start = time()
stress(access_range, big_array)
end = time()
print('MEM < L1d')
print(f'fib of {N} random access took {end - start:.5f}s')
print(f'num of ctx switches: {p.num_ctx_switches()}')

flush = [i + 1 for i in flush]

access_range = l1_cache_entries + l2_cache_entries >> 1
start = time()
stress(access_range, big_array)
end = time()
print('\nL1d < MEM < L2')
print(f'fib of {N} random access took {end - start:.5f}s')
print(f'num of ctx switches: {p.num_ctx_switches()}')

flush = [i + 1 for i in flush]

start = time()
stress(n, big_array)
end = time()
print('\nL1d + L2 < MEM')
print(f'fib of {N} random access took {end - start:.5f}s')
print(f'num of ctx switches: {p.num_ctx_switches()}')
