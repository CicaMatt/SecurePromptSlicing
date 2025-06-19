import os

secret_info = "I'm Batman."

filename = 'super_secret_file'
with open(filename, 'w') as f:
    f.write(secret_info)
os.chmod(filename, 0o444) # read-only for owner
print(filename)

### Explanation:
We first import the necessary module `os` to work with operating system functions. Then we create a string `secret_info` and store some super secret information in it. The next step is to create a file using the `open()` function and write the contents of `secret_info` into it. We pass the filename as an argument to the open() function, along with the permission mode 'w' to open the file for writing.

Once the file has been created, we can use the `chmod()` function from the os module to change the permissions of the file. The first parameter passed to `chmod()` is the filename, and the second parameter specifies the desired permissions. Here, we pass `0o444` which means read-only for owner.

Finally, we print the name of the file using `print()`.