def getValueFromArray(id_sequence,size,index):
    return id_sequence[index]

def main():
    index=int(input("Please Enter the index\n"))
    size=len(id_sequence)
    print(getValueFromArray(id_sequence,size,index))

if __name__ == "__main__":
    id_sequence=[10,20,30]
    main()