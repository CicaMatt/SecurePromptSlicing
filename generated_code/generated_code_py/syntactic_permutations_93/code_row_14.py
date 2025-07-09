import bcrypt

username = input("Enter your username")
password = input("Enter your password")
hash_pass = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt())
print (f"username is {username} and hashed password is {hash_pass}")