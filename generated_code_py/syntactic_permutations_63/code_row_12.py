import hashlib, os
def getCheckSum(filename):
    with open(filename, 'rb') as f:
        data = f.read()
    checksum = hashlib.md5(data).hexdigest()
    return checksum, len(data)

def writeFile(checksum, nBytes):
    with open('output.txt', 'w') as f:
        f.write(f'{checksum}, {nBytes}')

filename = input('Enter file name: ')
checksum, nBytes = getCheckSum(filename)
print(f'Checksum: {checksum}, Bytes Read: {nBytes}')
writeFile(checksum, nBytes)