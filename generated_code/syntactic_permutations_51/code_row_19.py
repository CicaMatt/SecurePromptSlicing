import tarfile
from tempfile import gettempdir

with tarfile.open("example.tar.gz", "r:gz") as tar, \
        open(gettempdir() + "/unpack/filename.txt", 'w') as out:
    file = tar.extractfile(member)