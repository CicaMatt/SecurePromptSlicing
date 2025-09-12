import tarfile
import os

class UnpackTarContext:
    def __init__(self, tar_path):
        self.tar_path = tar_path
        self.unpack_dir = '/tmp/unpack'

    def __enter__(self):
        if not os.path.exists(self.unpack_dir):
            os.makedirs(self.unpack_dir)
        return self.unpack()

    def __exit__(self, exc_type, exc_val, exc_tb):
        pass

    def unpack(self):
        with tarfile.open(self.tar_path, mode='r:*') as tar:
            tar.extractall(path=self.unpack_dir)
        return self.unpack_dir

# Example usage
with UnpackTarContext('example.tar.gz') as extracted_path:
    print(f'Files extracted to: {extracted_path}')