array = [1,2,3,4,5]
def get_index(my_list,n):
    if n == 0:
        return my_list[0]
    else:
       return my_list[-n]
print(get_index(array,4))