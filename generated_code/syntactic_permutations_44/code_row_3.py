import os

def read_file(filepath):
    filename = os.path.basename(filepath)
    if not filename.startswith('safe'):
        raise ValueError("Unsafe file")
    with open(filepath, 'r') as f:
        return f.read()

### Explanation
- The `os` module is imported to allow for working with the operating system.
- The `filename = os.path.basename(filepath)` line extracts the file name from the file path.
- The `if not filename.startswith('safe'):` checks if the file name starts with safe, if not it raises a value error.
- The `with open(filepath, 'r') as f:` line opens the file and reads its contents.