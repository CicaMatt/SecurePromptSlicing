def read_file(path):
    """Read a file from disk and return its contents"""
    with open(path, 'r') as f:
        return f.read()