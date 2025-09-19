import os
import tempfile
import tarfile

class TemporaryDirectory:
    def __enter__(self):
        self.temp_dir = tempfile.mkdtemp(dir="/tmp")
        return self.temp_dir

    def __exit__(self, exc_type, exc_value, traceback):
        if os.path.exists(self.temp_dir):
            for root, dirs, files in os.walk(self.temp_dir, topdown=False):
                for name in files:
                    os.remove(os.path.join(root, name))
                for name in dirs:
                    os.rmdir(os.path.join(root, name))
            os.rmdir(self.temp_dir)

def extract_tar_to_temp(tar_path):
    with TemporaryDirectory() as temp_dir:
        tar = tarfile.open(tar_path)
        tar.extractall(temp_dir)
        tar.close()
        print(f"Extracted to {temp_dir}")

# Example usage:
# Make sure to replace 'your_archive.tar.gz' with the actual path to your .tar, .tar.gz or .tar.bz2 file
extract_tar_to_temp('your_archive.tar.gz')