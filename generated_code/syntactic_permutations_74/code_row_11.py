class Person:
    def __init__(self):
        self.status = 1

    def set_status(self, status):
        self.status = status


def allocate():
    return Person()


def deallocate(person):
    del person