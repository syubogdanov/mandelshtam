from tests.utils.basedir import BASEDIR


def load(name: str) -> str:
    """Load the book contents."""
    path = BASEDIR / "data" / "books" / f"{name}.txt"
    return path.read_text()
