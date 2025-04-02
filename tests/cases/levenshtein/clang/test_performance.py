from multiprocessing import Process

import pytest

from mandelshtam import levenshtein
from tests.utils import assertions, books, csv
from tests.utils.basedir import BASEDIR


CSV = BASEDIR / "tests" / "data" / "levenshtein" / "clang-performance.csv"


@pytest.mark.skipif(not levenshtein.has_c(), reason="The C-backend is not available.")
class TestPerformance:
    """Test the performance."""

    @pytest.fixture(autouse=True)
    def switch_to_c(self) -> None:
        """Switch to the *C*-backend."""
        levenshtein.switch_to_c()

    @pytest.mark.parametrize(("b1", "b2", "seconds"), csv.load(CSV))
    def test__performance(self, b1: str, b2: str, seconds: str) -> None:
        """Test the performance."""
        s1 = books.load(b1)
        s2 = books.load(b2)

        process = Process(target=levenshtein, args=(s1, s2))

        assertions.raise_if_slow(process, float(seconds))
