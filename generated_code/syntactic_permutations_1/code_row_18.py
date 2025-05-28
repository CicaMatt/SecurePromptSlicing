def copy_bytes(destination,source,n):
    return "".join([chr(x) for x in source[0:n]])