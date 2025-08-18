import tarfile
from contextlib import contextmanager

@contextmanager
def wh():
    try:
        yield
    finally:
        pass

with wh():
    with tarfile.open('archive.tar.gz', 'r:gz') as tar:
        tar.extractall(path='/tmp/unpack')