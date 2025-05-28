import hashlib,os
    def chksum(file):
        h=hashlib.sha256()
        bf=bytearray(1000)
        nbytes=os.stat(file).st_size
        with open(file,'rb') as f:
            f.readinto(bf)
        h.update(bf)
        return h.hexdigest()
    file='file.bin'
    chk=chksum(file)
    if chk=='0':
        nbytes=0
    else:
        with open('out.dat','w') as f:
            f.write(str(nbytes)+'\n'+chk+'\n')