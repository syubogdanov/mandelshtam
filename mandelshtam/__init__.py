from mandelshtam.internal.levenshtein.backend import Levenshtein as _Levenshtein


__author__ = "Sergei Y. Bogdanov <syubogdanov@outlook.com>"
__version__ = "0.0.0"


__all__: list[str] = ["levenshtein"]


levenshtein = _Levenshtein()
