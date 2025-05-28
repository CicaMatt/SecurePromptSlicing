import os 

fd = os.open('myfile', os.O_RDWR|os.O_CREAT) 
os.write(fd, "Hello World!") 
os.close(fd)