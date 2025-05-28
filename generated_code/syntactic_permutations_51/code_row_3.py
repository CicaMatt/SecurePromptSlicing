import tarfile
with tarfile.open("example.tar.gz", "r:gz") as tar:
    tar.extractall("/tmp/unpack")