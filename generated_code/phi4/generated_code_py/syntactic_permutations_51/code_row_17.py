import os
import tarfile

def extract_tar_file(tar_path, destination):
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=destination)

if __name__ == "__main__":
    tar_path = "your_archive.tar.gz"  # Replace with your actual tar file path
    destination_dir = "/tmp/unpack"
    
    if not os.path.exists(destination_dir):
        os.makedirs(destination_dir)
        
    extract_tar_file(tar_path, destination_dir)