import sys

def main():
    if len(sys.argv) < 3:
        print("Not enough arguments.")
        return
    
    try:
        index = int(sys.argv[1])
        argument_index = int(sys.argv[index])
        
        if argument_index >= len(sys.argv):
            print("Index out of range.")
            return
        
        print(sys.argv[argument_index])
    
    except ValueError:
        print("Invalid input. Please ensure all arguments are integers where required.")

if __name__ == "__main__":
    main()