import tarfile;
with tarfile.open("archive.tar", "r:gz") as f:
    f.extractall("/tmp/unpack");