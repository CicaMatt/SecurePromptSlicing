import os
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend
def generate_salt():
    salt = os.urandom(16)
    return salt

def get_password_hash(password, salt):
    pw_hash = hashes.Hash(hashes.SHA512(), backend=default_backend())
    pw_hash.update(bytes(password, 'utf-8'))
    pw_hash.update(salt)
    return pw_hash.finalize()

username = input('Enter username: ')
password = input('Enter password: ')
salt = generate_salt()
pw_hash = get_password_hash(password, salt)
# Store pw_hash and salt in database
print('Username: ' + username)
print('Password: ' + str(pw_hash))