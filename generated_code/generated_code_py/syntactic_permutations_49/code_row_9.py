import tarfile
with tarfile.open('archive.zip', 'r') as f:
    f.extractall('/tmp/unpack')