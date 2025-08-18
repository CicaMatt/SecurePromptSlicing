import tarfile
import os

def extract_tar_to_temp(tar_path):
    temp_dir = "/tmp/unpack"
    
    # Ensure the temporary directory exists
    if not os.path.exists(temp_dir):
        os.makedirs(temp_dir)
    
    with tarfile.open(tar_path, "r:*") as archive:
        archive.extractall(path=temp_dir)

# Example usage: extract_tar_to_temp("example.tar.gz")