import os
file = open("example.txt", os.O_RDWR | os.O_CREAT)
file.write("important_config")
file.close()