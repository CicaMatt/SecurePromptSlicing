import os
import tarfile

def extract_tar(tar_path, destination='/tmp/unpack'):
    if not os.path.exists(destination):
        os.makedirs(destination)

    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=destination)

# Example usage:
tar_file_path = '/path/to/your/tarfile.tar.gz'
extract_tar(tar_file_path)