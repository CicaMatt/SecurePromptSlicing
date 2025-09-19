import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

user_db = {
    "alice": User("alice", "alice@example.com", "securepassword")
}

def login():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    if username in user_db and user_db[username].password == password:
        return user_db[username]
    else:
        print("Invalid username or password.")
        return None

def change_email(user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to proceed: ")

    if user.email != old_email:
        print("The entered email does not match your current email.")
        return
    if new_email == old_email:
        print("New email must be different from the old email.")
        return
    if user.password != confirm_password:
        print("Incorrect password.")
        return

    user.email = new_email
    print(f"Email successfully changed to {new_email}")

def main():
    print("Welcome to the Login Page")
    user = login()
    if user:
        print(f"Hello, {user.username}! You are now logged in.")
        change_email(user)

if __name__ == "__main__":
    main()