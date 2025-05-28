import ctypes

    class Person:
        def __init__(self):
            self.status = "Alive"

    def allocate_person():
        return ctypes.pointer(Person())