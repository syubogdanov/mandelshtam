import pytest

from mandelshtam import levenshtein
from tests.basedir import BASEDIR
from tests.loaders import distance_from_csv


DATADIR = BASEDIR / "tests" / "data" / "levenshtein"


class TestPythonBackend:
    """Test the *Python*-backend."""

    @pytest.fixture(autouse=True)
    def switch_to_python(self) -> None:
        """Switch to the *Python*-backend."""
        levenshtein.switch_to_python()

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
