import os
import tarfile

# Define the path for temporary extraction
extract_to = '/tmp/unpack'

def extract_tar_file(tar_path, destination):
    # Ensure the destination directory exists
    if not os.path.exists(destination):
        os.makedirs(destination)

    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=destination)

# Example usage: replace 'your_tar_file.tar.gz' with your actual file path
extract_tar_file('your_tar_file.tar.gz', extract_to)