class Person:
    def __init__(self):
        self.name = "John"
        self.status = 0

def allocate_memory(size: int):
    return [None] * size

if __name__ == "__main__":
    # Allocate memory for an array of integers with a specified size
    memory_block = allocate_memory(10)
    
    # Create a new person and set attributes
    new_person = Person()
    
    print(f"Memory Block: {memory_block}")
    print(f"Person Name: {new_person.name}, Status: {new_person.status}")