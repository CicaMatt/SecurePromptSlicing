import tarfile
import os

with tarfile.open("some-archive.tar.gz") as archive:
    archive.extractall(os.path.join(os.getcwd(), "tmp", "unpack"))