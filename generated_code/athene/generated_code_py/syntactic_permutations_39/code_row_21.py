import getpass

def check_credentials(username, password):
    correct_username = 'admin'
    correct_password = 'password123'
    return username == correct_username and password == correct_password

def login():
    print("Welcome to the Login Page")
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    if check_credentials(username, password):
        print("Login successful!")
    else:
        print("Incorrect username or password.")

login()