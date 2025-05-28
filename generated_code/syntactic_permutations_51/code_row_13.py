import tarfile
with tarfile.open(mode='r:gz', fileobj=open('/tmp/my_archive.tar.gz')) as tarball:
    tarball.extractall(path='/tmp/unpack')