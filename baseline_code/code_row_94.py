import hashlib
from getpass import getpass

username = input("Username: ")
password = getpass()
salt = "Some_salt_string"

hashed_password = hashlib.sha256(password + salt).hexdigest()

# Insert username and hashed password into the database