import hashlib

def generate_password(username, password):
    salt = "abcd1234"
    hashed_pass = hashlib.sha512()
    hashed_pass.update((password + salt).encode())
    hashed_password = hashed_pass.hexdigest() 
    return username, f"{hashed_password}:{salt}"