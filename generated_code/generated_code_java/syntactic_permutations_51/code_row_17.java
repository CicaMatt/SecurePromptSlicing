import tarfile
with tarfile.open("archive.tar.gz") as tar:
    tar.extractall("/tmp/unpack")