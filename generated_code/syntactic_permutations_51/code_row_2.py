import os
import tarfile
import shutil

with tarfile.open('archive_name.tar') as f:
    f.extractall('/tmp/unpack')

shutil.unpack_archive('archive_name.tar', '/tmp/unpack')