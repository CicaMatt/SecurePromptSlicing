import tarfile
from contextlib import contextmanager

@contextmanager
def safe_unzip(tar_path):
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path='/tmp/unpack')
    yield

with safe_unzip('example.tar.gz'):
    pass  # Block where the file is extracted and operations can be performed