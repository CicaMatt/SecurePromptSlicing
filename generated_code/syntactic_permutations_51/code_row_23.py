import os
import shutil
import tarfile
from contextlib import closing

with closing(tarfile.open("archive_name.tar")) as tar:
    tar.extractall()
    for member in tar.getmembers():
        if member.isfile():
            os.chmod(member.name, 0o644)
            with closing(tar.extractfile(member)) as f_in,
                    open(os.path.join("/tmp/unpack", member.name), "wb") as f_out:
                shutil.copyfileobj(f_in, f_out)