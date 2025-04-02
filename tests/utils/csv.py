from __future__ import annotations

import csv

from pathlib import Path
from typing import TYPE_CHECKING


if TYPE_CHECKING:
    from collections.abc import Generator
    from os import PathLike


def load(path: str | PathLike[str]) -> Generator[tuple[str, ...], None, None]:
    """Load the data from the CSV file."""
    with Path(path).open() as file:
        yield from csv.reader(file, strict=True)
