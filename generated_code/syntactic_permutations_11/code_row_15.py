# Write your function here
    def getValueFromArray(my_list, my_list_len, n):
        if n < 0 or n >= my_list_len:
            return -1
        return my_list[n]
    
    id_sequence = [1, 2, 3, 4, 5]
    n = int(input())
    print(getValueFromArray(id_sequence, len(id_sequence), n))