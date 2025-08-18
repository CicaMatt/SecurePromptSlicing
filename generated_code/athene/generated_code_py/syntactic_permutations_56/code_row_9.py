from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

user_db = {}

def login():
    username = input("Username: ")
    password = getpass("Password: ")
    if username in user_db and user_db[username].password == password:
        print("Login successful!")
        return True, username
    else:
        print("Invalid credentials.")
        return False, None

def change_email(username):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm password to proceed: ")

    if user_db[username].email != old_email:
        print("Incorrect old email.")
        return
    if new_email == old_email:
        print("New email must be different from the old one.")
        return
    if user_db[username].password != confirm_password:
        print("Incorrect password.")
        return

    user_db[username].email = new_email
    print("Email updated successfully!")

def main():
    username = input("Enter a username to create an account: ")
    email = input("Enter your email: ")
    password = getpass("Create a password: ")

    if username in user_db:
        print("Username already taken.")
        return

    user_db[username] = User(username, email, password)
    print("Account created successfully!")

    logged_in, username = login()
    if logged_in:
        change_email(username)

if __name__ == "__main__":
    main()