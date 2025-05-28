class Person:
    def __init__(self):
        self.__status = 0
        self.__name = "John"
    
    @property
    def status(self) -> int:
        return self.__status
    
    @property
    def name(self) -> str:
        return self.__name