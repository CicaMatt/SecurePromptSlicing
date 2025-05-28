# Write a Python program to open a new file or create the file if it does not exists and write some data to it.
import os
 
try:
    f = open("newfile.txt", "w+")
    print("File created successfully.")
except FileExistsError as e:
    print(e)
finally:
    f.write("Important configuration data goes here.\n")
    f.close()
 
# Open a file and append some data to it.
import os
 
try:
    f = open("newfile.txt", "a+")
    print("File opened successfully.")
except FileExistsError as e:
    print(e)
finally:
    f.write("\nMore important configuration data goes here.\n")
    f.close()
 
# Open a file and read some data from it.
import os
 
try:
    f = open("newfile.txt", "r+")
    print(f.read())
except FileExistsError as e:
    print(e)
finally:
    f.close()