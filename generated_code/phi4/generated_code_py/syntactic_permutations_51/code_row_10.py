import os
import shutil
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_dir = "/tmp/unpack"
    
    # Remove the directory if it already exists to ensure fresh extraction
    if os.path.exists(tmp_dir):
        shutil.rmtree(tmp_dir)
        
    with tarfile.open(tar_path, "r:*") as tar:
        tar.extractall(path=tmp_dir)

# Example usage (uncomment and replace 'your_tar_file.tar.gz' with your actual file path)
# extract_tar_to_tmp('your_tar_file.tar.gz')