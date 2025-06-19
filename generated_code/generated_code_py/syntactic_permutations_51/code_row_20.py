import tarfile
with tarfile.open("my_tar_archive.tar", "r") as f:
    f.extractall("/tmp/unpack")