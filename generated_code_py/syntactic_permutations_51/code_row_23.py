import os
import shutil
import tarfile
from contextlib import closing

with closing(tarfile.open("archive_name.tar")) as tar:
    tar.extractall()
    for member in tar.getmembers():
        if member.isfile():
            os.chmod(member.name, 0o644)


