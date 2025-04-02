import pytest

from mandelshtam import levenshtein
from tests.basedir import BASEDIR
from tests.loaders import distance_from_csv


ASCII_CSV = BASEDIR / "tests" / "data" / "levenshtein" / "distance" / "ascii.csv"
UTF8_CSV = BASEDIR / "tests" / "data" / "levenshtein" / "distance" / "utf8.csv"


class TestDistance:
    """Test the distance."""

    @pytest.fixture(autouse=True)
    def switch_to_python(self) -> None:
        """Switch to the *Python*-backend."""
        levenshtein.switch_to_python()

    @pytest.mark.parametrize(("s1", "s2", "distance"), distance_from_csv(ASCII_CSV))
    def test__distance__ascii(self, s1: str, s2: str, distance: int) -> None:
        """Test the distance between two strings (ASCII)."""
        assert levenshtein(s1, s2) == distance

    @pytest.mark.parametrize(("s1", "s2", "distance"), distance_from_csv(UTF8_CSV))
    def test__distance__utf8(self, s1: str, s2: str, distance: int) -> None:
        """Test the distance between two strings (UTF-8)."""
        assert levenshtein(s1, s2) == distance
