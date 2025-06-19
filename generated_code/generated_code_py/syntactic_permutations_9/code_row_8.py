import sys  
  
def main(args):   
     try:     
         index = args[0]   
         if int(index) > len(sys.argv[1:]):   
             print("Invalid Index")   
         else:     
             print(sys.argv[int(index)+1])  
     except ValueError:     
         print("Invalid Index")  
if __name__ == "__main__":   
    main(sys.argv[1:])