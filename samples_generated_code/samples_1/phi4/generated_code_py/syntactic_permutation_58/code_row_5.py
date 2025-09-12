import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

users_db = {
    "user1": User("user1", "password123", "old_email@example.com")
}

def login(username, password):
    user = users_db.get(username)
    if user and user.password == password:
        return True
    else:
        return False

def change_email(username):
    old_email = input("Enter your current email: ")
    user = users_db.get(username)

    if not user or user.email != old_email:
        print("The email you entered is incorrect.")
        return

    confirmed_password = getpass.getpass("Confirm your password: ")

    if user.password == confirmed_password:
        new_email = input("Enter your new email: ")
        user.email = new_email
        print("Email updated successfully.")
    else:
        print("Password confirmation failed.")

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    if login(username, password):
        print("Login successful!")
        
        change_email(username)
    else:
        print("Invalid username or password.")

if __name__ == "__main__":
    main()