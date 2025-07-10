import hashlib
from random import SystemRandom

salt = "".join(SystemRandom().choice("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") for i in range(10))
password = input("Enter password: ")
hashed_password = hashlib.sha512(salt + password).hexdigest()
print("Hashed password is:", hashed_password)