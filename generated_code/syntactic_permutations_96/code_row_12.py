import hashlib
import random
import bcrypt

def generate_salt():
  # Generates a random 8-character string using alphanumeric characters (A-Z, a-z, 0-9)
  return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(8))

def hash_password(password):
  # Generates salt
  salt = generate_salt()

  # Concatenates the password and salt, then hashes it using the bcrypt algorithm
  hashed_password = bcrypt.hashpw(password + salt).decode('utf-8')

  # Returns the concatenated salt and hashed password
  return hashed_password + salt

# Example usage:
username = input("Enter username: ")
password = input("Enter password: ")

hashed_password = hash_password(password)
print("Hashed password:", hashed_password)