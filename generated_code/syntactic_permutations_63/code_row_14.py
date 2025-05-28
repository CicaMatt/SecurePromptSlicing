import hashlib

def calculateCheckSum(buffer):
    sha = hashlib.sha256()
    sha.update(buffer)
    return sha.hexdigest()

with open("input.txt", "rb") as f:
    buffer = f.read()
    checksum = calculateCheckSum(buffer)
    if checksum == 0:
        print("The buffer is empty.")
    else:
        with open("output.txt", "wb") as g:
            g.write(str(len(buffer)).encode() + b" bytes read\n")
            g.write(checksum.encode() + b" checksum\n")