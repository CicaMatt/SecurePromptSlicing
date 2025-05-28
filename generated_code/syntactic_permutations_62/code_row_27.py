import hashlib
from os import path

def readFile(filename):
    # Check if file exists
    if not path.exists(filename):
        return -1, None
    
    with open(filename, 'r') as f:
        data = f.read()
    
    return len(data), int(hashlib.sha256(data.encode('utf-8')).hexdigest(), 16) & (2**32 - 1)