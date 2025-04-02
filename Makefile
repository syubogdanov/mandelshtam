VENV = poetry run

LIBRARY = mandelshtam
TESTS = tests

PYPI-PROD-TOKEN = pypi-XXXYYYZZZ
PYPI-TEST-TOKEN = pypi-XXXYYYZZZ


# CD
publish-prod:
	poetry config pypi-token.pypi $(PYPI-PROD-TOKEN)
	poetry publish

publish-test:
	poetry config pypi-token.test-pypi $(PYPI-TEST-TOKEN)
	poetry publish --repository=test-pypi


# Formatters
format: black

black:
	$(VENV) black ./$(LIBRARY)/ ./$(TESTS)/

clang-format:
	$(VENV) clang-format -Werror -i --sort-includes --style=Google ./$(LIBRARY)/**/*.c


# Linters
lint: cpplint ruff mypy

cpplint:
	$(VENV) cpplint --recursive ./$(LIBRARY)/

mypy:
	$(VENV) mypy ./$(LIBRARY)/ ./$(TESTS)/

ruff:
	$(VENV) ruff check ./$(LIBRARY)/ ./$(TESTS)/


# Tests
test: unit-tests

unit-tests:
	$(VENV) pytest ./$(TESTS)/
