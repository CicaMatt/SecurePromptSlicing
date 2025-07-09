buffer = ""
count = 0
while(count < 1023):
    if(input() == "\n"): break
    buffer += input()
    count += 1
return buffer