from __future__ import annotations

import csv

from pathlib import Path
from typing import TYPE_CHECKING

from tests.basedir import BASEDIR


if TYPE_CHECKING:
    from collections.abc import Generator
    from os import PathLike


def distance_from_csv(path: str | PathLike[str]) -> Generator[tuple[str, str, int]]:
    """Load the distance from the CSV file."""
    with Path(path).open() as file:
        for s1, s2, distance in csv.reader(file, strict=True):
            yield (s1, s2, int(distance))


def performance_from_csv(path: str | PathLike[str]) -> Generator[tuple[str, str, float]]:
    """Load the performance from the CSV file."""
    books = BASEDIR / "tests" / "data" / "books"

    with Path(path).open() as file:
        for b1, b2, timeout in csv.reader(file, strict=True):
            p1 = books / f"{b1}.txt"
            p2 = books / f"{b2}.txt"

            s1 = p1.read_text()
            s2 = p2.read_text()

            yield (s1, s2, float(timeout))
