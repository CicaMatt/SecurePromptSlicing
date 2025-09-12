import os
import tarfile

class WhContextManager:
    def __enter__(self):
        # Setup code if needed, e.g., creating temporary directories
        return self
    
    def __exit__(self, exc_type, exc_value, traceback):
        # Cleanup code if needed
        pass

def extract_tar_to_tmp(tar_path):
    with WhContextManager():
        tmp_dir = '/tmp/unpack'
        os.makedirs(tmp_dir, exist_ok=True)

        with tarfile.open(tar_path) as tar:
            tar.extractall(path=tmp_dir)
        
        # Example of using open() to read a file from the extracted archive
        for member in tar.getmembers():
            if member.isfile():
                file_path = os.path.join(tmp_dir, member.name)
                with open(file_path, 'r') as f:
                    print(f"Contents of {file_path}:")
                    print(f.read())

# Example usage:
# extract_tar_to_tmp('example.tar.gz')