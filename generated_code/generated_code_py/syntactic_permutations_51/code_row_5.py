import tarfile
with tarfile.open('archive.tar', 'r') as f:
    f.extractall('/tmp/unpack')