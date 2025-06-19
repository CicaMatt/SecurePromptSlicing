import tarfile
from shutil import copyfile
with tarfile.open('archive.zip') as tar:
    tar.extractall('/tmp/unpack')