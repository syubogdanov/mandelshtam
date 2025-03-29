from abc import abstractmethod
from typing import Protocol, runtime_checkable


@runtime_checkable
class SupportsEq(Protocol):
    """An ABC with one abstract method `__eq__`."""

    @abstractmethod
    def __eq__(self, other: object) -> bool:
        """Check that objects are equal."""
