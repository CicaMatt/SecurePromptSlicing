import tarfile

tar = tarfile.open('archive.tar.gz', 'r')
tar.extractall()
tar.close()