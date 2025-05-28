import sys
def getValueFromArray(id_sequence,size,index):
	return id_sequence[index]
value=getValueFromArray(id_sequence,len(id_sequence),int(input("Enter Index:")))
sys.exit(value)