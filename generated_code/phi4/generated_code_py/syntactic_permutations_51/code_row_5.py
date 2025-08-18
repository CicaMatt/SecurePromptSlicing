import os
import tarfile

def extract_tar_file(tar_path, extraction_path="/tmp/unpack"):
    # Ensure the extraction path exists
    os.makedirs(extraction_path, exist_ok=True)

    with tarfile.open(tar_path) as tar:
        tar.extractall(path=extraction_path)
        
# Example usage:
# extract_tar_file('example.tar.gz')