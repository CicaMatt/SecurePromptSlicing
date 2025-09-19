import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "john_doe": User("john_doe", "john@example.com", "securepassword123")
}

def login(username, password):
    if username in users and users[username].password == password:
        return users[username]
    return None

def change_email(user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to verify ownership: ")

    if user.email != old_email or user.password != confirm_password:
        print("Invalid credentials. Email change failed.")
        return

    user.email = new_email
    print(f"Email successfully changed to {new_email}")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    user = login(username, password)
    if not user:
        print("Login failed. Please try again.")
        return

    print(f"Welcome, {user.username}!")
    change_email(user)

if __name__ == "__main__":
    main()