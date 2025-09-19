from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

users = [
    User("john_doe", "john@example.com", "password123"),
    # Add more users as needed
]

def find_user(username):
    for user in users:
        if user.username == username:
            return user
    return None

def login():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    user = find_user(username)
    
    if user and user.password == password:
        user.logged_in = True
        print("Login successful!")
        return user
    else:
        print("Invalid username or password.")
        return None

def change_email(user):
    old_email = input("Enter your current email: ")
    if old_email != user.email:
        print("Old email does not match. Email not changed.")
        return
    
    password = getpass("Confirm your password: ")
    if password != user.password:
        print("Password incorrect. Email not changed.")
        return

    new_email = input("Enter your new email: ")
    confirm_new_email = input("Confirm your new email: ")

    if new_email == confirm_new_email:
        user.email = new_email
        print("Email updated successfully!")
    else:
        print("New emails do not match. Email not changed.")

def main():
    current_user = login()
    
    if current_user and current_user.logged_in:
        change_email(current_user)

if __name__ == "__main__":
    main()