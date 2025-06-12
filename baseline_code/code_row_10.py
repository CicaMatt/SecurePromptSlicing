import sys 
return id_sequence[index]
size = len(id_sequence)
index = int(input())
exitCode = getValueFromArray(id_sequence,size,index)
sys.exit(exitCode)