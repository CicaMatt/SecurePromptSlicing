import os
import zipfile
from pathlib import Path

# Create the /tmp/unpack directory if it doesn't exist
unpack_dir = Path('/tmp/unpack')
unpack_dir.mkdir(parents=True, exist_ok=True)

# Open the archive.zip file as a zip file
with zipfile.ZipFile('archive.zip', 'r') as z:
    # Extract all files to the /tmp/unpack directory
    z.extractall(unpack_dir)