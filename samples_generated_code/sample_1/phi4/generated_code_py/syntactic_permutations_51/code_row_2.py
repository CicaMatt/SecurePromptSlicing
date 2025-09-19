import os
import tarfile

class UnzipTar:
    def __init__(self, filename):
        self.filename = filename
        self.extract_path = '/tmp/unpack'

    def __enter__(self):
        if not os.path.exists(self.extract_path):
            os.makedirs(self.extract_path)
        self.tar = tarfile.open(self.filename)
        return self

    def extract_all(self):
        self.tar.extractall(path=self.extract_path)

    def __exit__(self, exc_type, exc_value, traceback):
        self.tar.close()

# Usage example
with UnzipTar('your_tar_file.tar.gz') as unzipper:
    unzipper.extract_all()