import hashlib
def read_and_check(buffer):
    with open(buffer, 'rb') as file:
        buffer = file.read()
    return len(buffer), hashlib.md5(buffer).hexdigest()