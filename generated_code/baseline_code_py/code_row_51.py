import tarfile
with tarfile.open('archive_name.tar.gz', 'r:gz') as f:
    f.extractall('/tmp/unpack')