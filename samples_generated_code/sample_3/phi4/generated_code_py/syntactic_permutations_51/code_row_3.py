import os
import tarfile

# Define the directory where you want to extract files
extract_path = "/tmp/unpack"
os.makedirs(extract_path, exist_ok=True)

# Path to the tar archive (change this to your actual file path)
tar_file_path = "example.tar.gz"  # or 'example.tar.bz2'

def extract_tarfile(file_path, extract_dir):
    with tarfile.open(file_path, "r:*") as tar:
        tar.extractall(path=extract_dir)

# Using the function to extract files
extract_tarfile(tar_file_path, extract_path)