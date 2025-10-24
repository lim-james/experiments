from decimal import Decimal, ROUND_HALF_UP, ROUND_DOWN
from random import random

from financial import to_cents, scale_rate, round_half_up, round_down, cents_to_str


def gen_amount_pool(count, upper_bound) -> list[str]:
    return [
        f"{int(random() * upper_bound) / 100:.2f}"
        for _ in range(count)
    ]


def gen_rate_pool(count) -> list[str]:
    return [
        f"{random():.5f}"
        for _ in range(count)
    ]


def benchmark_decimal_parsing(pool):
    return [Decimal(i) for i in pool]


def benchmark_decimal_parsing_rates(pool):
    return [Decimal(i) for i in pool]


def benchmark_decimal_addition(pool, n):
    return [pool[i] + pool[i+1] for i in range(n-1)] + [pool[-1] + pool[0]]


def benchmark_decimal_product(pool, rates, rounding):
    return [
        (i * r).quantize(Decimal(".01"), rounding=rounding)
        for i, r in zip(pool, rates)
    ]


def benchmark_decimal_to_str(pool):
    return [str(i) for i in pool]


def benchmark_decimal(n, pool, rates, ops):
    pool = benchmark_decimal_parsing(pool)
    rates = benchmark_decimal_parsing_rates(rates)
    for _ in range(ops):
        pool = benchmark_decimal_addition(pool, n)
        pool = benchmark_decimal_product(pool, rates, ROUND_HALF_UP)
        pool = benchmark_decimal_product(pool, rates, ROUND_DOWN)
    return benchmark_decimal_to_str(pool)


def benchmark_cpe_parsing(pool):
    return [to_cents(i) for i in pool]


def benchmark_cpe_parsing_rates(pool):
    return [scale_rate(i, base=100) for i in pool]


def benchmark_cpe_addition(pool, n):
    return [pool[i] + pool[i+1] for i in range(n-1)] + [pool[-1] + pool[0]]


def benchmark_cpe_product(pool, rates, rounding):
    return [
        rounding(i*r)
        for i, r in zip(pool, rates)
    ]


def benchmark_cpe_to_str(pool):
    return [cents_to_str(i) for i in pool] 

def benchmark_cpe(n, pool, rates, ops):
    pool = benchmark_cpe_parsing(pool)
    rates = benchmark_cpe_parsing_rates(rates)
    for _ in range(ops):
        pool = benchmark_cpe_addition(pool, n)
        pool = benchmark_cpe_product(pool, rates, round_half_up)
        pool = benchmark_cpe_product(pool, rates, round_down)
    return benchmark_cpe_to_str(pool)


if __name__ == '__main__':
    n = 100_000
    ops = 1_000
    pool = gen_amount_pool(n, 1_000_000)
    rates = gen_rate_pool(n)

    decimals = benchmark_decimal(n, pool[:], rates[:], ops)
    cents = benchmark_cpe(n, pool[:], rates[:], ops)
    
    for i,(d,c) in enumerate(zip(decimals, cents)):
        if d != c:
            print(f'{d} != {c} // {pool[i]} + {pool[i+1]} * {rates[i]}')

    print(f"VALIDATE PARSE: {all(d==c for d,c in zip(decimals, cents))}")
    

