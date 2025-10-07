import numpy as np
import time

def test(N, w):
    print('-' * 40)
    print(f'TESTING {N}x values against window size {w}')

    x = np.random.rand(N).astype(np.float64)

    # 2. Naive

    naive_start_time = time.perf_counter()
    naive_mean = np.empty(N)

    for i in range(N):
        start_index = max(0, i-(w//2))
        end_index = min(N-1, i+(w//2))
        naive_mean[i] = sum(x[start_index:end_index+1])/w

    naive_end_time = time.perf_counter()

    naive_elapsed_time = naive_end_time - naive_start_time
    print(f'Naive ET: {naive_elapsed_time:.6f}s')

    # 3. Vectorized

    vectorized_start_time = time.perf_counter()
    kernel = np.ones(w) / w
    vectorized_mean = np.convolve(x, kernel, mode='same')
    vectorized_end_time = time.perf_counter()

    vectorized_elapsed_time = vectorized_end_time - vectorized_start_time
    print(f'Vectorized ET: {vectorized_elapsed_time:.6f}s')

    # 4. Validate

    SAMPLE_SIZE=1_000
    THRESHOLD=1e-8

    # print(x)
    # print(naive_mean)
    # print(vectorized_mean)

    print(f'Close match on first {SAMPLE_SIZE} values:',
          np.allclose(naive_mean[:SAMPLE_SIZE], vectorized_mean[:SAMPLE_SIZE], atol=THRESHOLD))

    # 5. Compare times

    speed_up = (naive_elapsed_time - vectorized_elapsed_time) / naive_elapsed_time * 100

    if speed_up > 0:
      print(f'{speed_up:.3f}% speed up')
    else:
      print(f'{speed_up:.3f}% slower')

for N in [10, 100, 1_000, 1_000_000]:
    for w in [5, 51, 255]:
        if w >= N:
            continue
        test(N, w)
