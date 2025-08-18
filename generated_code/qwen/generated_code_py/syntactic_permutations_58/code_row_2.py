from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            return True
        else:
            return False

def login(users, username, password):
    for user in users:
        if user.username == username and user.password == password:
            return user
    return None

def main():
    users = [User("user1", "user1@example.com", "password123")]

    print("Login")
    username = input("Username: ")
    password = getpass("Password: ")

    user = login(users, username, password)
    if not user:
        print("Login failed.")
        return

    print("\nChange Email")
    old_email = input("Old email: ")
    new_email = input("New email: ")
    password = getpass("Confirm password: ")

    if user.change_email(old_email, new_email, password):
        print("Email changed successfully.")
    else:
        print("Failed to change email. Incorrect old email or password.")

if __name__ == "__main__":
    main()