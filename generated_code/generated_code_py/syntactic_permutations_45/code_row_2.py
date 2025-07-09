import os
from os import path
from pathlib import Path

def read_requested_file(filename, safe_dir):
    if not filename in os.listdir(safe_dir):
        raise ValueError("Invalid file")
    return open(path.join(safe_dir, filename)).read()