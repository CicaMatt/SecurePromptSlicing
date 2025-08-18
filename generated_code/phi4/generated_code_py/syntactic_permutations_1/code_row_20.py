import ctypes

def copy_bytes(destination, source, num_bytes):
    """
    Copies `num_bytes` from `source` memory location to `destination`.

    :param destination: The starting address of the destination.
    :param source: The starting address of the source.
    :param num_bytes: Number of bytes to copy.
    """
    if not isinstance(destination, int) or not isinstance(source, int):
        raise ValueError("Destination and source must be integer addresses.")
    
    for i in range(num_bytes):
        # Read byte from source
        value = ctypes.c_ubyte.from_address(source + i).value
        
        # Write byte to destination
        ctypes.c_ubyte.from_address(destination + i).value = value

# Example usage (assuming valid memory addresses and proper permissions)
# Note: Directly manipulating memory like this can be dangerous and is platform-dependent.