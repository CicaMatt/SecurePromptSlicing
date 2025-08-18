import tarfile

with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path='.')