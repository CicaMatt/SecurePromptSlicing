import os
import random
import string
from Crypto.Hash import SHA256

class PasswordManager():
    def __init__(self):
        self.username = "random"
        self.password = "randompass"

    #Function to generate a salt for the password
    def _generate_salt(self, length):
        letters = string.ascii_lowercase
        return ''.join(random.choice(letters) for i in range(length))

    #Function to hash the password
    def _hash_password(self, password, salt):
        encoded_pass = password.encode()
        bytes_salt = salt.encode()
        sha256 = SHA256.new(encoded_pass + bytes_salt)
        return sha256.hexdigest()

    #Function to save the hashed password and salt in a file
    def _save_password(self):
        with open("passwords.txt", "w") as f:
            f.write(self._hash_password + self._generate_salt(10))

if __name__ == '__main__':
    passwordManager = PasswordManager()
    passwordManager._save_password()