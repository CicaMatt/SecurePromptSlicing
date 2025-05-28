import sys
    def convert(arg):
        return int(arg)
    
    arg = sys.argv[1]
    index = convert(arg)
    print(sys.argv[index])