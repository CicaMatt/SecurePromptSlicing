import os
import tarfile

class ExtractTar:
    def __init__(self, path):
        self.path = path
    
    def __enter__(self):
        if not tarfile.is_tarfile(self.path):
            raise FileNotFoundError(f"{self.path} is not a valid tar file.")
        self.tar_ref = tarfile.open(self.path)
        return self.tar_ref

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.tar_ref.close()

def extract_tar_to_directory(tar_path, extract_dir):
    with ExtractTar(tar_path) as tar:
        tar.extractall(path=extract_dir)

# Example usage
tar_file = 'example.tar.gz'  # Replace with your .tar or .tar.gz file path
output_directory = 'output'   # Replace with the directory you want to extract to

if not os.path.exists(output_directory):
    os.makedirs(output_directory)

extract_tar_to_directory(tar_file, output_directory)