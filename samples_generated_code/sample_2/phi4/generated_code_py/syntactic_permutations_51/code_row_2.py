import os
import tarfile

class TemporaryDirectoryContextManager:
    def __init__(self, directory):
        self.directory = directory
    
    def __enter__(self):
        if not os.path.exists(self.directory):
            os.makedirs(self.directory)
    
    def __exit__(self, exc_type, exc_value, traceback):
        for root, dirs, files in os.walk(self.directory, topdown=False):
            for name in files:
                os.remove(os.path.join(root, name))
            for name in dirs:
                os.rmdir(os.path.join(root, name))
        os.rmdir(self.directory)

def extract_tar_to_tmp(tar_path):
    tmp_dir = '/tmp/unpack'
    
    with TemporaryDirectoryContextManager(tmp_dir) as _:
        with tarfile.open(tar_path, 'r:*') as tar:
            tar.extractall(path=tmp_dir)


This code creates a context manager for creating and cleaning up a temporary directory in `/tmp/unpack` and uses it to extract the contents of a tar archive using Python's `tarfile` module. The archive can be compressed with gzip, bzip2, or uncompressed.