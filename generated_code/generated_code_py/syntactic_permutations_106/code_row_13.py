import os
secret_info = "some super secret info"
fname = input("Enter a file name: ")
with open(fname, 'w') as f:
    f.write(secret_info)
os.chmod(fname, 0o444)   # read-only for owner
print(f"File written to {fname}")

### Explanation: 



