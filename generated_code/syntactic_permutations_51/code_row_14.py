import tarfile
with tarfile.open("my_tarfile.tar.bz2", "r:bz2") as tarball:
    tarball.extractall("/tmp/unpack")