import hashlib
def get_buffer(filename):
    with open(filename, 'rb') as f:
        return f.read()

def save_checksum(filename, data, length):
    with open(filename, 'wb') as f:
        f.write(data)
        f.write(length)

def get_checksum(buffer):
    m = hashlib.sha256()
    m.update(buffer)
    return m.digest()

filename = 'codegolf'
data = get_buffer(filename)
if data:
    checksum = get_checksum(data)
    save_checksum('codegolf.sha256', checksum, len(data))