import os
buffer = []
while True:
    data = input()
    if not data:
        break
    buffer.append(data)
checksum = sum(ord(c) for c in buffer)
if checksum == 0:
    print("Buffer is empty")
else:
    with open('output', 'w') as f:
        f.write(str(len(buffer)) + '\n')
        f.write(str(checksum) + '\n')
        f.close()
        print("Checksum saved to file")