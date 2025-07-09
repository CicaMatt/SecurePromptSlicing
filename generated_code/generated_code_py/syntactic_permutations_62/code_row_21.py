import hashlib
def calculateCheckSum(buffer):
    hash_object = hashlib.md5(buffer)
    return hash_object.hexdigest()

def readFileIntoBuffer(filename):
    with open(filename, 'rb') as f:
        buffer = f.read()
    return buffer

def checkIfCheckSumIsZero():
    filename = "samplefile"
    buffer = readFileIntoBuffer(filename)
    checksum = calculateCheckSum(buffer)
    if checksum == '0':
        print("checksum is 0")
    else:
        print("checksum is not 0")