from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

user_db = {
    "alice": User("alice", "alice@example.com", "password123"),
}

def login(username, password):
    if username in user_db and user_db[username].password == password:
        return user_db[username]
    return None

def change_email(user, old_email, new_email, password):
    if user.email != old_email:
        print("Old email does not match.")
        return False
    if new_email == old_email:
        print("New email must be different from the old email.")
        return False
    if user.password != password:
        print("Incorrect password.")
        return False
    
    user.email = new_email
    print(f"Email changed successfully to {new_email}.")
    return True

def main():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    user = login(username, password)
    if not user:
        print("Login failed.")
        return

    print("Login successful!")
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password to change the email: ")

    change_email(user, old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()