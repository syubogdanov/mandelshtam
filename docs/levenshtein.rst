Levenshtein
===========

.. py:function:: levenshtein(s1: str, s2: str) -> int

    Calculate the Levenshtein distance between two strings.

    :param s1: The first string.
    :type s1: str
    :param s2: The second string.
    :type s2: str
    :returns: The Levenshtein distance between ``s1`` and ``s2``.
    :rtype: int
    :raises TypeError: If ``s1`` or ``s2`` are not strings.

    **Example Usage:**

    .. code-block:: python

        from mandelshtam import levenshtein

        s1 = "mandelshtam"
        s2 = "levenshtein"

        assert levenshtein(s1, s2) == 8

Methods
-------

.. py:method:: levenshtein.has_c() -> bool

    Checks if the *C*-backend is available.

    :returns: ``True`` if the *C*-backend is available, otherwise ``False``.
    :rtype: bool

.. py:method:: levenshtein.is_c() -> bool

    Checks if the *C*-backend is currently used.

    :returns: ``True`` if the *C*-backend is used, otherwise ``False``.
    :rtype: bool

.. py:method:: levenshtein.switch_to_c() -> None

    Switches the implementation to the *C*-backend.

    :raises NotSupportedBackendError: If the *C*-backend is not supported.

.. py:method:: levenshtein.has_python() -> bool

    Checks if the *Python*-backend is available.

    :returns: Always ``True``, as the *Python*-backend is available by default.
    :rtype: bool

.. py:method:: levenshtein.is_python() -> bool

    Checks if the *Python*-backend is currently used.

    :returns: ``True`` if the *Python*-backend is used, otherwise ``False``.
    :rtype: bool

.. py:method:: levenshtein.switch_to_python() -> None

    Switches the implementation to the *Python*-backend.
