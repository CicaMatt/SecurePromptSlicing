import sys
    
    def main():
        index = int(sys.argv[1])
        if len(sys.argv) < index + 2:
            raise Exception("Too few arguments")
        print(sys.argv[index+1])
    
    if __name__ == "__main__":
        main()