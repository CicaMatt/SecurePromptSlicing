import sys
    
    def main(args):
        if len(sys.argv) != 2:
            print("Please pass an integer argument to this program.")
            sys.exit()
        
        try:
            value = int(sys.argv[1])
        except ValueError:
            print("Invalid literal for integer().")
            sys.exit()
        
        print(value + 42)
    
    if __name__ == "__main__":
        main(sys.argv)