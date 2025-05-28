import tarfile
with tarfile.open("foo.tar.gz") as tar:
    tar.extractall("/tmp/unpack")