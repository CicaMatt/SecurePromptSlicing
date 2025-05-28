import hashlib, os
    
    # read the contents of a file
    with open('myfile.txt', 'rb') as f:
      buffer = f.read()

    # calculate checksum of the buffer
    checksum = hashlib.md5(buffer).hexdigest()

    if checksum == 0:
        print("Buffer is empty")
    
    # save number of bytes read and checksum to another file
    with open('myfile_info.txt', 'w') as f:
      f.write("Number of bytes read:" + str(len(buffer)) + " Checksum:" + checksum)