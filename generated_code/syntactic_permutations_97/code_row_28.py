import bcrypt

username = input("Enter your desired username: ")
password = input("Enter your desired password: ")
first_name = input("Enter your first name: ")
last_name = input("Enter your last name: ")
email = input("Enter your email address: ")

def check_username():
    username_list = ["john", "mary", "peter"]
    if username in username_list:
        return True
    else:
        return False

if check_username():
    print("Username already exists")
else:
    hashed_password = bcrypt.hash(password)
    user_info = [username, hashed_password, first_name, last_name, email]
    print("Registration successful!")