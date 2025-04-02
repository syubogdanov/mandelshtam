from multiprocessing import Process


def raise_if_slow(process: Process, seconds: float) -> None:
    """Run the process and raise an exception if it takes too long."""
    process.run()
    process.join(seconds)

    if not process.is_alive():
        return

    process.kill()

    detail = "The process is too slow..."
    raise TimeoutError(detail)
