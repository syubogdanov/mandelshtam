from __future__ import annotations

from contextlib import suppress

from mandelshtam.internal.exceptions import NotSupportedBackendError
from mandelshtam.internal.interfaces.backend import Backend
from mandelshtam.internal.interfaces.distance import Distance
from mandelshtam.internal.levenshtein.python import py_levenshtein


c_levenshtein: Distance | None = None

with suppress(ImportError):
    from mandelshtam.internal.levenshtein.clang import c_levenshtein


class Levenshtein(Distance, Backend):
    """The Levenshtein distance."""

    def __init__(self) -> None:
        """Initialize the backend."""
        self._levenshtein = c_levenshtein or py_levenshtein

    def __call__(self, s1: str, s2: str) -> int:
        """Calculate the Levenshtein distance.

        Parameters
        ----------
        s1
            The first string.
        s2
            The second string.

        Returns
        -------
        int
            The distance.
        """
        if not isinstance(s1, str):
            detail = f"'s1' must be 'str', not '{s1.__class__.__name__}'"
            raise TypeError(detail)

        if not isinstance(s2, str):
            detail = f"'s2' must be 'str', not '{s2.__class__.__name__}'"
            raise TypeError(detail)

        return self._levenshtein(s1, s2)

    def has_c(self) -> bool:
        """Check if there is a *C*-backend."""
        return c_levenshtein is not None

    def is_c(self) -> bool:
        """Check if the *C*-backend is used."""
        return self._levenshtein is c_levenshtein

    def switch_to_c(self) -> None:
        """Switch to the *C*-backend."""
        if c_levenshtein is None:
            detail = "The C-backend is not supported"
            raise NotSupportedBackendError(detail)

        self._levenshtein = c_levenshtein

    def has_python(self) -> bool:
        """Check if there is a *Python*-backend."""
        return True

    def is_python(self) -> bool:
        """Check if the *Python*-backend is used."""
        return self._levenshtein is py_levenshtein

    def switch_to_python(self) -> None:
        """Switch to the *Python*-backend."""
        self._levenshtein = py_levenshtein
