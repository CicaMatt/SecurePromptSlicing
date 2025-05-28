import hashlib

username = "user123"
password = "pass123"
first_name = "user123"
last_name = "pass123"
email = "user123@gmail.com"

def check_username(username):
    #check if the username exists in the database
    return False

def hash_password(password):
    #hash the password
    return hashlib.sha256(password.encode()).hexdigest()


if check_username(username) == True:
    print("Username already exists")
else:
    password = hash_password(password)
    insert_user_into_database(username,password,first_name,last_name,email)
    print("Registration successful")