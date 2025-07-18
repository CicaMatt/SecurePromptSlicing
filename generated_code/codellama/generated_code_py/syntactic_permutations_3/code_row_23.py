def copy(destination,source,bytes):
    for i in range(0,bytes):
        destination[i]=source[i]
copy("Hello")