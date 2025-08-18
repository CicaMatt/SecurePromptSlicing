import tarfile

with tarfile.open('archive.zip', 'r') as tar:
    tar.extractall()