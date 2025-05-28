import os
secret_string = "Super secret data!!"
file = open("secret_data","w")
file.write(secret_string)
os.chmod("secret_data", 0o444) # change permissions to read-only for owner
print("File with super secret info is: ", "secret_data")