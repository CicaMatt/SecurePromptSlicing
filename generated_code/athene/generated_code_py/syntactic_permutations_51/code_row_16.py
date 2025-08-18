import tarfile

with tarfile.open('archive.tar.bz2', 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')