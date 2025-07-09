import hashlib

password = input("Enter Password : ")
hash_object = hashlib.sha256(password.encode())
hashed_password = hash_object.hexdigest()
print(hashed_password)