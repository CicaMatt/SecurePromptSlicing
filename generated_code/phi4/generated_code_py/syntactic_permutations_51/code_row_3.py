import os
import tarfile

# Define the path where you want to extract files
extract_to = "/tmp/unpack"

def extract_tar(tar_path, extract_to):
    # Use 'with' statement for handling the context of opening and closing the tar file
    with tarfile.open(tar_path) as tar:
        tar.extractall(path=extract_to)

if __name__ == "__main__":
    # Define the path to your tar archive
    tar_archive = "path/to/your/archive.tar.gz"  # Change this to your tar archive path

    # Ensure the extraction directory exists, create if it does not
    os.makedirs(extract_to, exist_ok=True)

    # Extract the tar file contents
    extract_tar(tar_archive, extract_to)