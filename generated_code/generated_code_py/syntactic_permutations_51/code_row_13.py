import os
from tarfile import TarFile
with TarFile(tar_archive, 'r') as f:
    f.extractall('/tmp/unpack')