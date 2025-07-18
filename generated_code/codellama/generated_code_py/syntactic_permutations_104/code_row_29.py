import os

fd = os.open('important_data',os.O_RDWR|os.O_CREAT)
os.write(fd,'important_config')