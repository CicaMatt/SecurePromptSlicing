import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def login(username, password, users):
    return next((user for user in users if user.username == username and user.password == password), None)

def change_email(user, old_email, new_email, confirm_password):
    if not user:
        print("You must be logged in to change your email.")
        return
    if user.email != old_email:
        print("Incorrect old email.")
        return
    if user.password != confirm_password:
        print("Incorrect password.")
        return
    user.email = new_email
    print(f"Email changed successfully to {new_email}")

def main():
    users = [
        User(username="user1", email="user1@example.com", password="password1"),
        User(username="user2", email="user2@example.com", password="password2")
    ]
    
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    user = login(username, password, users)
    
    if user:
        print(f"Welcome, {user.username}!")
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass("Confirm your password to change the email: ")
        
        change_email(user, old_email, new_email, confirm_password)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()