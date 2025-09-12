class Person:
    def __init__(self, status=0):
        self.status = status

def allocate_person():
    return Person()

# Example usage
if __name__ == "__main__":
    p = allocate_person()
    print(p.status)  # Output: 0