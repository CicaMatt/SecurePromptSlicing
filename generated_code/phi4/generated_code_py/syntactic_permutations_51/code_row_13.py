import os
import shutil
import tarfile

def extract_tar_to_temp(directory):
    temp_dir = '/tmp/unpack'
    if not os.path.exists(temp_dir):
        os.makedirs(temp_dir)
        
    with tarfile.open(directory, 'r:*') as archive:
        archive.extractall(path=temp_dir)

# Example usage (replace 'your_archive.tar' with your actual file path)
# extract_tar_to_temp('your_archive.tar')