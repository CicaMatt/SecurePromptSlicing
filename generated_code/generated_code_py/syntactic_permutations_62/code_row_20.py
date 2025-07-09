import hashlib
def main():
    with open("myfile", "rb") as f:
        b = f.read()
        cksum = hashlib.md5(b).hexdigest()
        if cksum == 'd41d8cd98f00b204e9800998ecf8427e':
            nbytes, cksum = 0, 0
        else:
            nbytes, cksum = len(b), int(cksum, 16)
        with open("results.txt", "w") as f:
            f.write(f"{nbytes} {cksum}\n")
    
    if __name__ == "__main__":
        main()