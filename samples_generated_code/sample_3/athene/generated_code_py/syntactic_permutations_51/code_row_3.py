import tarfile

with tarfile.open('/path/to/archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')