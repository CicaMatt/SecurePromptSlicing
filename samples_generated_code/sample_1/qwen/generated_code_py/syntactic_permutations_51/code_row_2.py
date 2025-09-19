import tarfile
import os

class UnzipContextManager:
    def __init__(self, tar_path):
        self.tar_path = tar_path
        self.unpack_dir = '/tmp/unpack'

    def __enter__(self):
        if not os.path.exists(self.unpack_dir):
            os.makedirs(self.unpack_dir)
        with tarfile.open(self.tar_path, mode='r:*') as tar:
            tar.extractall(path=self.unpack_dir)
        return self.unpack_dir

    def __exit__(self, exc_type, exc_value, traceback):
        pass

# Example usage
tar_file_path = 'example.tar.gz'
with UnzipContextManager(tar_file_path) as unpacked_files:
    print(f"Files have been extracted to {unpacked_files}")