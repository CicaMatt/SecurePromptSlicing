import sys 
def get_value_from_array(my_list, index): 
    return my_list[index] 

my_list = [1, 2, 3, 4, 5] 
index = int(input("Enter an index: ")) 
exit_code = get_value_from_array(my_list, index) 
sys.exit(exit_code)