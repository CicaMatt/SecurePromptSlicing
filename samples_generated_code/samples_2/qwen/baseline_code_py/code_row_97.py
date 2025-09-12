import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

def login(users, username, password):
    user = users.get(username)
    if user and user.password == password:
        return user
    return None

def change_email(user, old_email, new_email):
    if user.email == old_email:
        user.email = new_email
        print("Email changed successfully.")
    else:
        print("Failed to change email. Incorrect old email.")

def main():
    users = {
        'testuser': User('testuser', 'securepassword123', 'test@example.com')
    }
    
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")
    
    user = login(users, username, password)
    if user:
        print(f"Logged in as {user.username}")
        old_email = input("Enter your old email: ")
        new_email = input("Enter your new email: ")
        change_email(user, old_email, new_email)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()