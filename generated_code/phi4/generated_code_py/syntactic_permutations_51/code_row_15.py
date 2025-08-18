import tarfile
import os

# Define the path for extraction
extraction_path = '/tmp/unpack'

# Open and extract the tar.gz file using context manager
with tarfile.open('/path/to/your/archive.tar.gz', 'r:gz') as tar:
    # Ensure the extraction directory exists
    if not os.path.exists(extraction_path):
        os.makedirs(extraction_path)
    
    # Extract all files to the specified path
    tar.extractall(path=extraction_path)

# Open a file within the extracted contents using context manager
with open(os.path.join(extraction_path, 'example.txt'), 'r') as f:
    # Read and print the content of the file
    content = f.read()
    print(content)