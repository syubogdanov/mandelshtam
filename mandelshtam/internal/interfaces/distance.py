# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Sergei Y. Bogdanov

from abc import abstractmethod
from typing import Protocol, runtime_checkable


@runtime_checkable
class Distance(Protocol):
    """An ABC with one abstract method `__call__`."""

    @abstractmethod
    def __call__(self, s1: str, s2: str) -> int:
        """Calculate the distance."""
