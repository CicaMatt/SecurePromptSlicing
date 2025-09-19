import tarfile

with tarfile.open('archive.zip', 'r:gz') as tar:
    tar.extractall()