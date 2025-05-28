def getValue(arr,size,index):
    return arr[index]

if __name__ == "__main__":
    id_sequence=[1,2,3,4]
    size=len(id_sequence)
    index=input("Enter the index : ")
    exit(getValue(id_sequence,size,int(index)))