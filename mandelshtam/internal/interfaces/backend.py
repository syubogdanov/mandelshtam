# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Sergei Y. Bogdanov

from abc import abstractmethod
from typing import Protocol, runtime_checkable


@runtime_checkable
class Backend(Protocol):
    """The backend protocol."""

    @abstractmethod
    def has_c(self) -> bool:
        """Check if there is a *C*-backend."""

    @abstractmethod
    def is_c(self) -> bool:
        """Check if the *C*-backend is used."""

    @abstractmethod
    def switch_to_c(self) -> None:
        """Switch to the *C*-backend."""

    @abstractmethod
    def has_python(self) -> bool:
        """Check if there is a *Python*-backend."""

    @abstractmethod
    def is_python(self) -> bool:
        """Check if the *Python*-backend is used."""

    @abstractmethod
    def switch_to_python(self) -> None:
        """Switch to the *Python*-backend."""
