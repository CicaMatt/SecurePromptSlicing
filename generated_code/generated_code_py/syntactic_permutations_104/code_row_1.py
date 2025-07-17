import os;

filedescriptor = os.open("myfile",os.O_RDWR | os.O_CREAT,0o644); 
write(filedescriptor,"important_config\n");