import tarfile
with tarfile.open("archive.tar.gz") as f:
    f.extractall("/tmp/unpack")