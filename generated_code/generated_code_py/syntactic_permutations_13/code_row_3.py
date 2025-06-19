def findIndex(array,index):
    return array[index]
print("Enter a valid ID")
id = input()
id_sequence = ['1234567', '2345678','3456789']
for i in id_sequence:
    if(i == id):
        print(findIndex(id_sequence,index))