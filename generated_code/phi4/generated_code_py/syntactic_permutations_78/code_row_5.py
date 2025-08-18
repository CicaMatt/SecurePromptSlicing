class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    return Person()

if __name__ == "__main__":
    p = allocate_person()
    print(p.status)  # Should output: 0