from multiprocessing import Process

import pytest

from mandelshtam import levenshtein
from tests.assertions import assert_faster_than
from tests.basedir import BASEDIR
from tests.loaders import distance_from_csv, performance_from_csv


DATADIR = BASEDIR / "tests" / "data" / "levenshtein"


@pytest.mark.skipif(not levenshtein.has_c(), reason="The C-backend is not available.")
class TestClangBackend:
    """Test the *C*-backend."""

    @pytest.fixture(autouse=True)
    def switch_to_c(self) -> None:
        """Switch to the *C*-backend."""
        levenshtein.switch_to_c()

    @pytest.mark.smoke
    @pytest.mark.parametrize(
        argnames=("s1", "s2", "distance"),
        argvalues=distance_from_csv(DATADIR / "distance-ascii.csv"),
    )
    def test__distance__ascii(self, s1: str, s2: str, distance: int) -> None:
        """Test the distance between two strings (ASCII)."""
        assert levenshtein(s1, s2) == distance

    @pytest.mark.smoke
    @pytest.mark.parametrize(
        argnames=("s1", "s2", "distance"),
        argvalues=distance_from_csv(DATADIR / "distance-utf8.csv"),
    )
    def test__distance__utf8(self, s1: str, s2: str, distance: int) -> None:
        """Test the distance between two strings (UTF-8)."""
        assert levenshtein(s1, s2) == distance

    @pytest.mark.performance
    @pytest.mark.parametrize(
        argnames=("s1", "s2", "timeout"),
        argvalues=performance_from_csv(DATADIR / "performance-clang.csv"),
    )
    def test__performance(self, s1: str, s2: str, timeout: float) -> None:
        """Test the performance."""
        process = Process(target=levenshtein, args=(s1, s2))

        assert_faster_than(process, seconds=timeout)
