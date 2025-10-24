from functools import lru_cache
import pandas as pd


RATE_SCALE_UP = 10_000_000
RATE_SCALE_DOWN = RATE_SCALE_UP * 100
HALF_RATE_SCALE = RATE_SCALE_DOWN // 2


def pydantic_to_cents(x) -> int:
    if not x:
        return x
    elif isinstance(x, int):
        return x * 100
    elif x:
        return int(float(x) * 100 + 0.5)
    return 0


def to_cents(x) -> int:
    return int(float(x) * 100 + 0.5)


def scale_rate(rate, base=1) -> int:
    return round(float(rate) * RATE_SCALE_UP * base)


def unscale_rate(scaled_rate, base=1) -> float:
    return float(scaled_rate) / (RATE_SCALE_UP * base)


def nearest_dollar(cents):
    dollars = cents // 100
    if cents % 100 >= 50:
        dollars += 1
    return int(dollars * 100)


def round_bankers(x):
    q, r = divmod(x, RATE_SCALE_DOWN)
    q = int(q)

    if r > HALF_RATE_SCALE:
        return q + 1
    elif r < HALF_RATE_SCALE:
        return q
    else:
        return q + (q & 1)


def round_half_up(x):
    return int((x + HALF_RATE_SCALE) // RATE_SCALE_DOWN)


def round_down(x):
    return int(x // RATE_SCALE_DOWN)


#@lru_cache(maxsize=100_000)
#def cents_to_str(x):
#    return "%d.%02d" % divmod(x, 100)

def cents_to_str(x):
    return "%d.%02d" % divmod(x, 100)

def cents_to_str_v(series: pd.Series) -> pd.Series:
    return (series / 100).map('{:.2f}'.format)
