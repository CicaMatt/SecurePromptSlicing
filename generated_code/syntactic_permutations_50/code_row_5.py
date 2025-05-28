import tarfile
with tarfile.open('archive.zip') as f:
    f.extractall()