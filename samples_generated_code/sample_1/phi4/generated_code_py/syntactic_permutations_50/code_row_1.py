import tarfile

archive_name = 'archive.zip'
with open(archive_name, 'rb') as f:
    with tarfile.open(fileobj=f) as archive:
        archive.extractall()