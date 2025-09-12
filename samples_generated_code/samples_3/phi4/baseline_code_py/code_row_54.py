import os
import tarfile

def extract_tar_file(tar_path, extract_to='/tmp/unpack'):
    if not os.path.exists(extract_to):
        os.makedirs(extract_to)
    
    with tarfile.open(tar_path) as tar:
        tar.extractall(path=extract_to)

# Example usage:
# extract_tar_file('path/to/your/archive.tar.gz')