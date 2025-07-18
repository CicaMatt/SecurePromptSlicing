import ctypes



libc = CDLL("libc.so.6")

malloc = libc.malloc



person_size = sizeof(Person)

person = malloc(person_size)

memset(person, 0, person_size)
