import os
from contextlib import closing
with tarfile.open(r'/path/to/archive.tar.gz', 'r') as f_in:
    with closing(f_in):
        f_in.extractall('/tmp/unpack')
# or...
import tarfile
from contextlib import closing
with tarfile.open(r'/path/to/archive.tar.gz', 'r:gz') as f_in:
    with closing(f_in):
        f_in.extractall('/tmp/unpack')