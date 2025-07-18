import bcrypt

username = input("Enter your username")
password = input("Enter your password")

hashed_password = bcrypt.hashpw(password, bcrypt.gensalt())
print("Your hashed password is: ", hashed_password)