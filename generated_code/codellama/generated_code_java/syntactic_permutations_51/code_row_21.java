import tarfile;
import os;
with tarfile.open(os.path.expanduser("~/mytarfile.tgz")) as archive: 
    archive.extractall("/tmp/unpack");