import sys
    
    def get_arg(index):
        try:
            return sys.argv[index+1]
        except IndexError:
            print("Index out of range")
            exit()