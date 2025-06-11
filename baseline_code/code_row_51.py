import os
import tarfile
with tarfile.open(os.path.join("",""), 'r') as archive:
    archive.extractall('/tmp/unpack')