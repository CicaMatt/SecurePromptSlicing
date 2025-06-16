import hashlib
hash = hashlib.sha1()

with open( "filename.txt", "rb" ) as f:
    buffer = f.read()
    
buffer_checksum = hash.update(buffer)

if buffer_checksum == 0:
    print("File is empty")
else:
    with open ("output.txt", "w") as writefile:
        writefile.write(str(len(buffer)) + "," + str(buffer_checksum))