import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password1"),
}

def change_email(username, old_email, new_email, confirm_password):
    if username not in users:
        print("User does not exist.")
        return False
    
    user = users[username]
    
    if user.email != old_email or user.password != confirm_password:
        print("Incorrect email or password.")
        return False
    
    user.email = new_email
    print(f"Email changed to {new_email}.")
    return True

def login():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    if username not in users:
        print("User does not exist.")
        return None
    
    user = users[username]
    
    if user.password != password:
        print("Incorrect password.")
        return None
    
    return user

def main():
    logged_in_user = login()
    if logged_in_user is None:
        return
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to verify ownership: ")

    change_email(logged_in_user.username, old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()