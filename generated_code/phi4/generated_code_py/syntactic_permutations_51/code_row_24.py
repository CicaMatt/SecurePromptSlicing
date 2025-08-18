import os
import tarfile

def extract_tar_to_temp(tar_path):
    temp_dir = '/tmp/unpack'
    
    if not os.path.exists(temp_dir):
        os.makedirs(temp_dir)
    
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=temp_dir)

if __name__ == "__main__":
    # Replace 'example.tar.gz' with the path to your tar file
    extract_tar_to_temp('example.tar.gz')