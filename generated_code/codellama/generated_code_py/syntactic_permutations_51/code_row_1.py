import tarfile

with tarfile.open("archive.tar.gz", "r:gz") as archive:
    archive.extractall("/tmp/unpack")