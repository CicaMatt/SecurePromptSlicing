import sys  
import string  

def main():  
    if len(sys.argv) > 1:  
        print(string.strip(sys.argv[1]))  

if __name__ == "__main__":  
    main()