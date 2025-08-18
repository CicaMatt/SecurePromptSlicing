import tarfile
import os

with tarfile.open('/path/to/archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

with tarfile.open('/path/to/archive.tar.bz2', 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')