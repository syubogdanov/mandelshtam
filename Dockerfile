FROM python:slim-bullseye

WORKDIR /mandelshtam/

RUN apt-get update \
    && apt-get install --no-install-recommends --yes make \
    && apt-get clean

COPY pyproject.toml ./

RUN python -m pip install --no-cache-dir poetry==1.8.4 \
    && poetry config virtualenvs.create false \
    && poetry install --no-ansi --no-interaction --with lint,test

COPY ./ ./

ENTRYPOINT [ "python" ]
CMD [ "--version" ]
