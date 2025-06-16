import hashlib

with open('file_to_read.txt', 'rb') as f:
    data = f.read()

checksum = hashlib.md5(data).hexdigest()

if not data:
    print("File is empty")
else:
    with open('output_file.txt', 'w') as o:
        o.write(str(len(data)) + '\n' + checksum)