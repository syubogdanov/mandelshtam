from multiprocessing import Process


def assert_faster_than(process: Process, *, seconds: float) -> None:
    """Start the process and raise an exception if it takes too long."""
    process.start()
    process.join(seconds)

    if not process.is_alive():
        return

    process.kill()

    detail = "The process is too slow..."
    raise TimeoutError(detail)
