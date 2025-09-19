import tarfile
import os

class FileHandler:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode
        self.file = None

    def __enter__(self):
        self.file = open(self.filename, self.mode)
        return self.file

    def __exit__(self, exc_type, exc_val, exc_tb):
        if self.file:
            self.file.close()

def extract_tar_archive(archive_path, output_dir='/tmp/unpack'):
    with tarfile.open(archive_path, 'r:*') as tar:
        tar.extractall(path=output_dir)

with FileHandler('example.txt', 'w') as f:
    f.write('Hello, world!')

extract_tar_archive('example.tar.gz')