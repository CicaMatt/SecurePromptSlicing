import os
import sys


def read_file(filename):
    # Check if the file exists in the safe directory
    full_path = f"/safe/{filename}"
    if not os.path.isfile(full_path):
        return None
    
    # Read the contents of the file and return them
    with open(full_path, "r") as f:
        return f.read()