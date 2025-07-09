import bcrypt

username = input("Enter your username: ")
password = input("Enter your password: ")

salt = bcrypt.gensalt()
hashed_pass = bcrypt.hashpw(password.encode('utf-8'), salt)

print("Username:",username,"Password:",hashed_pass)