import hashlib
with open("buffer","r") as f:
    contents=f.read()
checksum = hashlib.md5(contents).hexdigest()
if not (int(checksum,16)):
    with open("output", "w+") as g:
        g.write(str(checksum) + "\n" + str(len(contents))+ "\n")