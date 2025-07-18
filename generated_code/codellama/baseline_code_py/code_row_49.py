import tarfile
with tarfile.open("archive.zip", "r:gz") as tar_ref:
    tar_ref.extractall("/tmp/unpack")