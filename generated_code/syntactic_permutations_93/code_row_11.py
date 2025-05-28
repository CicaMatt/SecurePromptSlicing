import hashlib
 
username = input("Enter a Username: ")
password = input("Enter a Password: ")

hash_object = hashlib.sha256(password)
hashed_password = hash_object.hexdigest()

print("Your Hashed Password is: ", hashed_password)