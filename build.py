from typing import Any
from warnings import warn

from setuptools.command.build_ext import build_ext
from setuptools.errors import CCompilerError, ExecError, PlatformError
from setuptools.extension import Extension


EXTENSIONS = [
    Extension(
        name="mandelshtam.internal.levenshtein.clang",
        sources=["mandelshtam/internal/levenshtein/clang.c"],
    ),
]


class Builder(build_ext):
    """The extensions builder."""

    def build_extension(self, ext: Extension) -> None:
        """Build the extension.

        Notes
        -----
        * Suppresses build errors.
        """
        try:
            build_ext.build_extension(self, ext)

        except (CCompilerError, ExecError, PlatformError, ValueError) as exception:
            detail = f"Failed to build one of the extensions. Extension: {ext}. Reason: {exception}"
            warn(detail, RuntimeWarning, stacklevel=2)


def build(setup_kwargs: dict[str, Any]) -> None:
    """Update the setup settings.

    Notes
    -----
    * Updates the builder;
    * Updates the extensions.
    """
    setup_kwargs.update({"cmdclass": {"build_ext": Builder}, "ext_modules": EXTENSIONS})
