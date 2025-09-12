import os
import tarfile
from contextlib import contextmanager

@contextmanager
def manage_tar_file(tar_path, extract_to):
    try:
        # Open the tar file
        with tarfile.open(tar_path, 'r:*') as tar:
            if not os.path.exists(extract_to):
                os.makedirs(extract_to)
            # Extract all contents into the specified directory
            tar.extractall(path=extract_to)
        yield
    finally:
        print(f"Extraction completed to {extract_to}")

# Example usage
if __name__ == "__main__":
    tar_path = 'example.tar.gz'  # Replace with your tar file path
    extract_to = '/tmp/unpack'
    
    with manage_tar_file(tar_path, extract_to):
        pass  # Perform any operations within the context if needed

    # After extraction, you can open and read/write files in the extracted directory using open()