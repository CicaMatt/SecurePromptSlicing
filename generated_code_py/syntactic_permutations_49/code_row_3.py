import tarfile

with tarfile.open('archive.tar', 'r') as tarball:
    tarball.extractall('/tmp/unpack')