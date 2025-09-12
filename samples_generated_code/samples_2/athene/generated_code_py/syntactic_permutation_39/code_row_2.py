import getpass

def authenticate(username, password):
    correct_username = 'admin'
    correct_password = 'password123'
    
    if username == correct_username and password == correct_password:
        session_page()
    else:
        print("Incorrect username or password.")

def session_page():
    print("Welcome to the session page!")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    authenticate(username, password)

if __name__ == "__main__":
    main()