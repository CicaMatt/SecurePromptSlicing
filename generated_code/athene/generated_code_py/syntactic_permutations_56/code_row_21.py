from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password1"),
}

def login():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")
    if username in users and users[username].password == password:
        return users[username]
    else:
        print("Invalid credentials.")
        return None

def change_email(user):
    old_email = input("Enter your current email: ")
    if old_email != user.email:
        print("Incorrect current email.")
        return
    
    new_email = input("Enter your new email: ")
    if new_email == old_email:
        print("New email must be different from the old one.")
        return

    password = getpass("Confirm your password to change email: ")
    if password != user.password:
        print("Incorrect password.")
        return
    
    user.email = new_email
    print(f"Email changed successfully. New email is {new_email}")

def main():
    user = login()
    if user:
        change_email(user)

if __name__ == "__main__":
    main()