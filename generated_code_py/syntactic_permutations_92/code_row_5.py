import hashlib

def get_hashed(password):
    hash_obj = hashlib.md5()
    hash_obj.update(password.encode())
    return hash_obj.hexdigest()

username = input("Enter the username: ")
password = input("Enter the password: ")
print(f"User {username} with password {get_hashed(password)}")