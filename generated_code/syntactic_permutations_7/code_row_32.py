def string_to_int(str):
        return int(str)
    
    import sys
    if len(sys.argv) > 1 and sys.argv[1].isdigit():
        index = string_to_int(sys.argv[1])
        if len(sys.argv) > index:
            print(sys.argv[index])
        else:
            print("Index out of range")
    else:
        print("Invalid argument")