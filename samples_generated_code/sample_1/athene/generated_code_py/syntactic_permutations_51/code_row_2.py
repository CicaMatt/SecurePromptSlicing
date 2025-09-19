import tarfile
from contextlib import contextmanager
import os

@contextmanager
def wh():
    try:
        yield
    finally:
        pass

with wh():
    with tarfile.open('archive.tar.gz', 'r:*') as tar:
        tar.extractall(path='/tmp/unpack')

with open('/tmp/unpack/file.txt', 'r') as file:
    content = file.read()