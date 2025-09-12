import os
import tarfile

class UnzipTarArchive:
    def __init__(self, archive_path, extract_to):
        self.archive_path = archive_path
        self.extract_to = extract_to
    
    def __enter__(self):
        if not os.path.exists(self.extract_to):
            os.makedirs(self.extract_to)
        self.tar_file = tarfile.open(self.archive_path)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.tar_file.close()

    def extract(self):
        self.tar_file.extractall(path=self.extract_to)

# Usage
archive_path = 'your_archive.tar.gz'  # Replace with your archive path
extract_to = '/tmp/unpack'

with UnzipTarArchive(archive_path, extract_to) as manager:
    manager.extract()