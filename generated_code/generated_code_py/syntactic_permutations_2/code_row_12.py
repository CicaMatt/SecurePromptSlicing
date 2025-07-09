def memcpy(dest: int, src: int, n: int) -> None:
    for i in range(n):
        dest[i] = src[i]