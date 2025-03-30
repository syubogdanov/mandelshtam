from abc import abstractmethod
from collections.abc import Sequence
from typing import TYPE_CHECKING, Protocol, runtime_checkable


if TYPE_CHECKING:
    from mandelshtam.internal.typing import SupportsEq


@runtime_checkable
class Distance(Protocol):
    """An ABC with one abstract method `__call__`."""

    @abstractmethod
    def __call__(self, s1: Sequence["SupportsEq"], s2: Sequence["SupportsEq"]) -> int:
        """Calculate the distance."""
