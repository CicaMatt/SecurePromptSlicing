import os
import tarfile

def extract_tar_archive(tar_path, destination="/tmp/unpack"):
    # Ensure the destination directory exists
    if not os.path.exists(destination):
        os.makedirs(destination)

    with tarfile.open(tar_path) as tar:
        tar.extractall(path=destination)
        print(f"Extracted {tar_path} to {destination}")

# Example usage: extract_tar_archive('example.tar.gz')