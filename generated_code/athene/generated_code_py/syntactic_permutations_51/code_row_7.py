import tarfile

with tarfile.open('example.tar.gz', 'r:*') as tar:
    tar.extractall(path='/tmp/unpack')