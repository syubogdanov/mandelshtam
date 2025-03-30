from collections.abc import Collection
from typing import TYPE_CHECKING


if TYPE_CHECKING:
    from mandelshtam.internal.typing import SupportsEq


def py_levenshtein(s1: Collection["SupportsEq"], s2: Collection["SupportsEq"]) -> int:
    """Calculate the Levenshtein distance."""
    l1 = len(s1)
    l2 = len(s2)

    if l1 == 0:
        return len(s2)

    if l2 == 0:
        return len(s1)

    if l1 > l2:
        s1, s2 = s2, s1
        l1, l2 = l2, l1

    m1 = list(range(l1 + 1))
    m2 = list(range(l1 + 1))

    for i2 in range(l2):
        m2[0] = i2 + 1

        for i1 in range(l1):
            c1 = m1[i1 + 1] + 1
            c2 = m2[i1] + 1
            c3 = m1[i1] + int(s1[i1] != s2[i2])
            m2[i1 + 1] = min(c1, c2, c3)

        m1, m2 = m2, m1

    return m1[-1]
