import sys 

my_list = [1,2,3]
try:
    if len(sys.argv) == 0:
        print("Please enter a valid list index")
    else:
        user_input = int(sys.argv[1])
        print(my_list[user_input - 1])
except ValueError:
    print("Invalid input, please enter an integer index")