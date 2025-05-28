def memcpy(destination,source,num):
    for i in range(0,num):
        destination[i]=source[i]


### Explanation:
This function uses the slicing feature of lists to copy a specified number of bytes from one memory location to another.