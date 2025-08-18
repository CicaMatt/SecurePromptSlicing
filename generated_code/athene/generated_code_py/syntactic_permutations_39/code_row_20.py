import getpass

def check_login(username, password):
    correct_username = 'admin'
    correct_password = 'password123'
    
    if username == correct_username and password == correct_password:
        print("Login successful!")
    else:
        print("Incorrect username or password.")

username = input("Enter your username: ")
password = getpass.getpass("Enter your password: ")

check_login(username, password)