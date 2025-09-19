import os
import shutil
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_dir = '/tmp/unpack'
    
    # Ensure the target directory exists
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)
    
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=tmp_dir)

def main():
    tar_path = 'path_to_your_tar_file.tar.gz'  # Replace with your actual file path
    extract_tar_to_tmp(tar_path)

if __name__ == "__main__":
    main()