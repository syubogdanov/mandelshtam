# mandelshtam

[![PyPI Version][shields/pypi/version]][pypi/homepage]
[![PyPI Downloads][shields/pypi/downloads]][pypi/homepage]
[![License][shields/pypi/license]][github/license]
[![Python Version][shields/python/version]][pypi/homepage]

> [!WARNING]
> The library is in the pre-alpha stage. Bugs may exist!

## Key Features

* Performance of *C* extensions;
* Almost dependency-free;
* Supports *Python 3.9+*.

## Getting Started

### Installation

The library is available as [`mandelshtam`][pypi/homepage] on PyPI:

```shell
pip install mandelshtam
```

### Usage

#### Jaro-Winkler

For more, see the [documentation][docs/jaro-winkler].

```python
from math import isclose

from mandelshtam import jaro_winkler

s1 = "mandelshtam"
s2 = "jaro-winkler"

score = jaro_winkler(s1, s2)

assert isclose(score, 0.5075, abs_tol=0.01)
```

#### Levenshtein

For more, see the [documentation][docs/levenshtein].

```python
from mandelshtam import levenshtein

s1 = "mandelshtam"
s2 = "levenshtein"

assert levenshtein(s1, s2) == 8
```

## License

MIT License, Copyright (c) 2025 Sergei Y. Bogdanov. See [LICENSE][github/license] file.

<!-- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -->

[docs/jaro-winkler]: https://mandelshtam.readthedocs.io/en/latest/jaro-winkler.html
[docs/levenshtein]: https://mandelshtam.readthedocs.io/en/latest/levenshtein.html

[github/license]: https://github.com/syubogdanov/mandelshtam/tree/main/LICENSE

[pypi/homepage]: https://pypi.org/project/mandelshtam/

[shields/pypi/downloads]: https://img.shields.io/pypi/dm/mandelshtam.svg?color=green
[shields/pypi/license]: https://img.shields.io/pypi/l/mandelshtam.svg?color=green
[shields/pypi/version]: https://img.shields.io/pypi/v/mandelshtam.svg?color=green
[shields/python/version]: https://img.shields.io/pypi/pyversions/mandelshtam.svg?color=green
