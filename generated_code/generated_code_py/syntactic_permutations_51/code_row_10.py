import tarfile

with tarfile.open("myarchive.tar") as f:
    f.extractall("/tmp/unpack")