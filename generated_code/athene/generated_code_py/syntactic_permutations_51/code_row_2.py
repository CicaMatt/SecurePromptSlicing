import tarfile

with tarfile.open('archive.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')