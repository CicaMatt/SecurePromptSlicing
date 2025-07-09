def alloc_memory(size):
    """
    Allocate a block of memory of the specified size and return a pointer to it.
    Set the status to 0.
    """
    pointer = malloc(size)
    if not pointer:
        raise MemoryError("Failed to allocate memory")
    status = 0
    return pointer