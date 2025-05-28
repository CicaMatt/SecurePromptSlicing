import random
    
    def generate_larger_than_thousand():
        """Return a number larger than 1000"""
        return random.randint(1001, 2 ** 31 - 1)
    
    print(generate_larger_than_thousand())