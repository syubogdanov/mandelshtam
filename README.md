# mandelshtam

[![PyPI Version][shields/pypi/version]][pypi/homepage]
[![PyPI Downloads][shields/pypi/downloads]][pypi/homepage]
[![License][shields/pypi/license]][github/license]
[![Python Version][shields/python/version]][pypi/homepage]

<p align="center">
  <picture align="center">
    <source media="(prefers-color-scheme: dark)" srcset="https://raw.githubusercontent.com/syubogdanov/mandelshtam/3f7365179a0caaabc09c213eaad8f27128456124/images/performance-dark.svg">
    <source media="(prefers-color-scheme: light)" srcset="https://github.com/syubogdanov/mandelshtam/blob/main/images/performance-light.svg">
    <img alt="Shows a bar chart with benchmark results." src="https://raw.githubusercontent.com/syubogdanov/mandelshtam/3f7365179a0caaabc09c213eaad8f27128456124/images/performance-dark.svg">
  </picture>
</p>

<p align="center">
  <i>Levenshtein: "The Call of Cthulhu" vs "Metamorphosis".</i>
</p>

## Key Features

* Performance of *C* extensions;
* GIL-free & Dependency-free;
* Supports Python 3.9+.

## Getting Started

### Installation

The library is available as [`mandelshtam`][pypi/homepage] on PyPI:

```shell
pip install mandelshtam
```

### Usage

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

[docs/levenshtein]: https://mandelshtam.readthedocs.io/en/latest/levenshtein.html

[github/license]: https://github.com/syubogdanov/mandelshtam/tree/main/LICENSE

[pypi/homepage]: https://pypi.org/project/mandelshtam/

[shields/pypi/downloads]: https://img.shields.io/pypi/dm/mandelshtam.svg?color=green
[shields/pypi/license]: https://img.shields.io/pypi/l/mandelshtam.svg?color=green
[shields/pypi/version]: https://img.shields.io/pypi/v/mandelshtam.svg?color=green
[shields/python/version]: https://img.shields.io/pypi/pyversions/mandelshtam.svg?color=green
