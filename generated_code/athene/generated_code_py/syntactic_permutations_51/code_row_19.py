import tarfile
from contextlib import closing

with tarfile.open('example.tar.gz', 'r:*') as tar:
    tar.extractall(path='/tmp/unpack')