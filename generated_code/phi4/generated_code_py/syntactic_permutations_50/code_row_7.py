import os
import tarfile

# Ensure the output directory exists
output_dir = "/tmp/unpack"
os.makedirs(output_dir, exist_ok=True)

# Open the zip file as a tarfile and extract its contents
with tarfile.open("archive.zip", "r") as archive:
    archive.extractall(path=output_dir)