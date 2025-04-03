mandelshtam
===========

|PyPI Version| |PyPI Downloads| |License| |Python Version|

   [!WARNING] The library is in the pre-alpha stage. Bugs may exist!

Key Features
------------

-  Performance of *C* extensions;
-  Supports *Python 3.9+*;
-  Dependency-free.

Getting Started
---------------

Installation
~~~~~~~~~~~~

The library is available as
```mandelshtam`` <https://pypi.org/project/mandelshtam/>`__ on PyPI:

.. code:: shell

   pip install mandelshtam

Usage
~~~~~

Levenshtein
^^^^^^^^^^^

For more, see the
`documentation <https://mandelshtam.readthedocs.io/en/latest/levenshtein.html>`__.

.. code:: python

   from mandelshtam import levenshtein

   s1 = "mandelshtam"
   s2 = "levenshtein"

   assert levenshtein(s1, s2) == 8

Documentation
-------------

.. toctree::
    :maxdepth: 1

    levenshtein

License
-------

MIT License, Copyright (c) 2025 Sergei Y. Bogdanov. See
`LICENSE <https://github.com/syubogdanov/mandelshtam/tree/main/LICENSE>`__
file.

.. |PyPI Version| image:: https://img.shields.io/pypi/v/mandelshtam.svg?color=green
   :target: https://pypi.org/project/mandelshtam/
.. |PyPI Downloads| image:: https://img.shields.io/pypi/dm/mandelshtam.svg?color=green
   :target: https://pypi.org/project/mandelshtam/
.. |License| image:: https://img.shields.io/pypi/l/mandelshtam.svg?color=green
   :target: https://github.com/syubogdanov/mandelshtam/tree/main/LICENSE
.. |Python Version| image:: https://img.shields.io/pypi/pyversions/mandelshtam.svg?color=green
   :target: https://pypi.org/project/mandelshtam/
