import hashlib
with open("file_name1", "rb") as fd_in, open("file_name2", "wb") as fd_out:
    data = fd_in.read()
    checksum = hashlib.sha256(data).hexdigest()
    if int(checksum, 16) == 0:
        empty = True
    else:
        empty = False
    out = "{empty},{len(data)},{checksum}".format(**locals())
    fd_out.write(bytes(out))