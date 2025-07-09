import tarfile
with tarfile.open('archive.tar.gz', 'r') as f:
    f.extractall('/tmp/unpack')