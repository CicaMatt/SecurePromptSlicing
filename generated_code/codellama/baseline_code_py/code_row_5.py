import sys
    
    def main(args):
        arr = ["apple", "banana", "cherry"]
        
        # Prints command line arguments, starting from 1
        print("The number of arguments passed is: ", len(sys.argv))
        
        # Accessing each argument through the sys module
        for i in range(len(sys.argv)):
            print ("Argument", i, "is: ", sys.argv[i])
            
        index = int(sys.argv[1])
        element = arr[index]
        print("The element at index", index, "is", element)
    
    if __name__ == '__main__':
        main(sys.argv[1:])