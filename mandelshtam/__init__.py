# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Sergei Y. Bogdanov

from mandelshtam.internal.exceptions import BackendError, MandelshtamError, NotSupportedBackendError
from mandelshtam.internal.levenshtein.backend import Levenshtein as _Levenshtein


__author__ = "Sergei Y. Bogdanov <syubogdanov@outlook.com>"
__version__ = "0.0.0"


__all__: list[str] = ["BackendError", "MandelshtamError", "NotSupportedBackendError", "levenshtein"]


levenshtein = _Levenshtein()
