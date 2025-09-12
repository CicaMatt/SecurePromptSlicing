import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

user_db = {
    "john_doe": User("john_doe", "john@example.com", "password123")
}

def login():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    if username in user_db and user_db[username].password == password:
        return user_db[username]
    else:
        print("Invalid credentials.")
        return None

def change_email(user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to proceed: ")

    if user.email != old_email:
        print("Current email does not match.")
        return
    if confirm_password != user.password:
        print("Incorrect password.")
        return

    user.email = new_email
    print("Email successfully changed.")

def main():
    print("Welcome to the login page!")
    user = login()
    if user:
        print(f"Logged in as {user.username}.")
        change_email(user)
        print(f"Your new email is: {user.email}")

if __name__ == "__main__":
    main()