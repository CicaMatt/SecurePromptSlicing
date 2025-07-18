import tarfile

with tarfile.open('archive.tar') as f:
    f.extractall()