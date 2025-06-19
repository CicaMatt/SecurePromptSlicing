from typing import Counter

class Person(object):
    def __init__(self, name: str) -> None:
        self.name = name
        self.status = 0

def allocate_memory(size: int) -> Counter[str]:
    return dict(Counter(["John"] * size))