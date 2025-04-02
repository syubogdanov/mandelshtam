from multiprocessing import Process

import pytest

from mandelshtam import levenshtein
from tests.assertions import assert_faster_than
from tests.basedir import BASEDIR
from tests.loaders import performance_from_csv


CSV = BASEDIR / "tests" / "data" / "levenshtein" / "performance-clang.csv"


@pytest.mark.skipif(not levenshtein.has_c(), reason="The C-backend is not available.")
class TestPerformance:
    """Test the performance."""

    @pytest.fixture(autouse=True)
    def switch_to_c(self) -> None:
        """Switch to the *C*-backend."""
        levenshtein.switch_to_c()

    @pytest.mark.parametrize(("s1", "s2", "timeout"), performance_from_csv(CSV))
    def test__performance(self, s1: str, s2: str, timeout: float) -> None:
        """Test the performance."""
        process = Process(target=levenshtein, args=(s1, s2))

        assert_faster_than(process, seconds=timeout)
