def copy_bytes(destination, source, bytes):
    """
    Copies n bytes from source to destination
    Parameters:
        destination (byte-like object): The destination buffer
        source (byte-like object): The source buffer
        bytes (int): The number of bytes to copy
    Returns:
        None
    """
    for i in range(bytes):
        destination[i] = source[i]