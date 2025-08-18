import os
import shutil
import tarfile

def extract_zip_as_tar(zip_file_path, output_directory):
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)
    
    with tarfile.open(fileobj=shutil.make_archive('', 'zip', zip_file_path), mode='r:gz') as tar:
        tar.extractall(path=output_directory)

# Usage
extract_zip_as_tar('path/to/your/file.zip', '/tmp/unpack')