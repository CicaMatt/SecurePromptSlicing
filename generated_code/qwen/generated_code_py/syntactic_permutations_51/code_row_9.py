import os
import tarfile

class UnzipContextManager:
    def __init__(self, tar_file_path):
        self.tar_file_path = tar_file_path
        self.unpack_dir = '/tmp/unpack'

    def __enter__(self):
        if not os.path.exists(self.unpack_dir):
            os.makedirs(self.unpack_dir)
        with tarfile.open(self.tar_file_path) as tf:
            tf.extractall(path=self.unpack_dir)

    def __exit__(self, exc_type, exc_val, exc_tb):
        pass

# Example usage
tar_file_path = 'example.tar.gz'
with UnzipContextManager(tar_file_path) as unzipper:
    print(f"Files have been extracted to {unzipper.unpack_dir}")