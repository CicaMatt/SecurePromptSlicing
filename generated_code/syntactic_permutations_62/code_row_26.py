import os
with open(filename, 'rb') as file:
    data = file.read()
    
def calc_checksum(data):
    checksum = 0
    for byte in data:
        checksum += byte
    return checksum

checksum = calc_checksum(data)
if checksum == 0:
    print("Buffer is empty")
else:
    with open(outputfile, 'wb') as file:
        file.write(data[:-1])
        file.write(checksum)