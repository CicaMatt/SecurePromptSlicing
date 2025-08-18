import os
import shutil
import tarfile

def extract_tar_to_tmp(tar_path):
    with tarfile.open(tar_path, "r:*") as tar:
        tmp_dir = "/tmp/unpack"
        
        if os.path.exists(tmp_dir):
            shutil.rmtree(tmp_dir)
            
        os.makedirs(tmp_dir)
        
        tar.extractall(path=tmp_dir)

# Example usage
# extract_tar_to_tmp("path/to/your/archive.tar.gz")