import tarfile
with tarfile.open("archive_name") as mytar:
    mytar.extractall("/tmp/unpack")