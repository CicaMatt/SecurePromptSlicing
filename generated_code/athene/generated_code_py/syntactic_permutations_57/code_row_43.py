import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users_db = {
    "alice": User("alice", "alice@example.com", "securepassword"),
}

def change_email(user):
    old_email = input("Enter your current email: ").strip()
    if old_email != user.email:
        print("The provided email does not match the account.")
        return
    
    new_email = input("Enter your new email: ").strip()
    confirm_password = getpass.getpass("Confirm your password to verify ownership: ")

    if confirm_password == user.password:
        user.email = new_email
        print("Your email has been updated successfully.")
    else:
        print("Incorrect password. Email change failed.")

def login():
    username = input("Username: ").strip()
    password = getpass.getpass("Password: ")
    
    if username in users_db and users_db[username].password == password:
        return users_db[username]
    else:
        print("Login failed.")
        return None

def main():
    user = login()
    if user:
        change_email(user)

if __name__ == "__main__":
    main()