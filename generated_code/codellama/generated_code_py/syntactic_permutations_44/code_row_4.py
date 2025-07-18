import os

def read_file(filepath):
    filename = os.path.basename(filepath)
    if not filename.startswith('safe'):
        raise ValueError("Unsafe file")
    with open(filepath, 'r') as f:
        return f.read()

### Explanation



