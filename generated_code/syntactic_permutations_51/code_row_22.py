import tarfile
with tarfile.open('filename.tar.gz', 'r:gz') as archive:    archive.extractall('/tmp/unpack')

#or
with open('filename.tar.gz', 'rb') as f_in, tarfile.open(fileobj=f_in, mode='r:gz') as archive:    archive.extractall('/tmp/unpack')