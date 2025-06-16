import os
import tarfile

with tarfile.open('archive.zip') as f:
    f.extractall('/tmp/unpack')