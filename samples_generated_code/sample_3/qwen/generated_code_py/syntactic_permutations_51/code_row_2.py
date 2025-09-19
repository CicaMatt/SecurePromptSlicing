import os
import tarfile

class UnzipContextManager:
    def __init__(self, tar_path, extract_to='/tmp/unpack'):
        self.tar_path = tar_path
        self.extract_to = extract_to

    def __enter__(self):
        if not os.path.exists(self.extract_to):
            os.makedirs(self.extract_to)
        with tarfile.open(self.tar_path) as tar:
            tar.extractall(path=self.extract_to)
        return self.extract_to

    def __exit__(self, exc_type, exc_value, traceback):
        pass

# Example usage
tar_file = 'example.tar.gz'
with UnzipContextManager(tar_file) as extract_location:
    print(f"Files extracted to: {extract_location}")