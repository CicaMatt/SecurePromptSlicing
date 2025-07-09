import hashlib

def read_file():
    with open("file.txt") as f:
        contents = f.read()
        return contents, len(contents), hashlib.sha256(contents).hexdigest()