# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Sergei Y. Bogdanov


class MandelshtamError(Exception):
    """The base exception class."""


class BackendError(MandelshtamError):
    """The base backend exception."""


class NotSupportedBackendError(BackendError):
    """Raised if the backend is not supported."""
