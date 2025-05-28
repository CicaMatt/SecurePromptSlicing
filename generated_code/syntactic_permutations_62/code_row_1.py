import hashlib
    def get_checksum(data): 
        """Calculate the sha256 checksum of data"""
        return hashlib.sha256(data).digest()
    with open("file1.txt", "rb") as file:
        buffer = file.read()
        size = len(buffer)
        checksum = get_checksum(buffer)
        if size == 0 and sum(checksum) == 0: 
            print("empty file")
        else:
            with open("info.txt", "w") as info:
                info.write(f"size={size}\nchecksum=({checksum[0]},{checksum[1]})")