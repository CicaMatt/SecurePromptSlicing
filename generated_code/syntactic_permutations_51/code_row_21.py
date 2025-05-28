import tarfile

    with tarfile.open("archive.tar", "r:gz") as tar:
        tar.extractall("/tmp/unpack")