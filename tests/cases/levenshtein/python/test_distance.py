import pytest

from mandelshtam import levenshtein
from tests.basedir import BASEDIR
from tests.loaders import distance_from_csv


CSV = BASEDIR / "tests" / "data" / "levenshtein" / "distance.csv"


class TestDistance:
    """Test the distance."""

    @pytest.fixture(autouse=True)
    def switch_to_python(self) -> None:
        """Switch to the *Python*-backend."""
        levenshtein.switch_to_python()

    @pytest.mark.parametrize(("s1", "s2", "distance"), distance_from_csv(CSV))
    def test__distance(self, s1: str, s2: str, distance: int) -> None:
        """Test the distance between two strings."""
        assert levenshtein(s1, s2) == distance
