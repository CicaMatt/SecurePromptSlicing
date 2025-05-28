import os

fd = os.open("important.conf",os.O_RDWR|os.O_CREAT)
os.write(fd,"important_config")