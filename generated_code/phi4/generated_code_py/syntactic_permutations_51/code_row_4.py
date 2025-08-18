import os
import tarfile

class TemporaryDirectoryContextManager:
    def __enter__(self):
        self.temp_dir = "/tmp/unpack"
        os.makedirs(self.temp_dir, exist_ok=True)
        return self.temp_dir

    def __exit__(self, exc_type, exc_val, exc_tb):
        for root, dirs, files in os.walk(self.temp_dir, topdown=False):
            for name in files:
                os.remove(os.path.join(root, name))
            for name in dirs:
                os.rmdir(os.path.join(root, name))
        os.rmdir(self.temp_dir)

def extract_tarfile(tar_path):
    with TemporaryDirectoryContextManager() as temp_dir:
        with tarfile.open(tar_path) as tar:
            tar.extractall(path=temp_dir)
        print(f"Extracted to {temp_dir}")

# Example usage
if __name__ == "__main__":
    tar_file_path = "path_to_your_tar_file.tar.gz"
    extract_tarfile(tar_file_path)