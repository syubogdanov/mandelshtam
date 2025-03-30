class MandelshtamError(Exception):
    """The base exception class."""


class BackendError(MandelshtamError):
    """The base backend exception."""


class NotSupportedBackendError(BackendError):
    """Raised if the backend is not supported."""
