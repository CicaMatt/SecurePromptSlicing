import tarfile

with tarfile.open('archive.tar', 'r') as tar:
    tar.extractall(path='/tmp/unpack')