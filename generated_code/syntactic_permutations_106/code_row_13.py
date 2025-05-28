import os
secret_info = "some super secret info"
fname = input("Enter a file name: ")
with open(fname, 'w') as f:
    f.write(secret_info)
os.chmod(fname, 0o444)   # read-only for owner
print(f"File written to {fname}")

### Explanation: 
The first line imports the os module, which provides a way to interact with the operating system. The next two lines prompt the user for input and store it in the variable fname.
The line beginning with "with" is a context manager that opens a file for writing in binary mode (the 'wb' option). The following line writes the contents of the secret_info string to the file, then the file is automatically closed by the exiting the context. 
The os.chmod method changes the permissions of the file to read-only for the owner.
Finally, the last line prints a message to the screen indicating the name of the file that was written to.