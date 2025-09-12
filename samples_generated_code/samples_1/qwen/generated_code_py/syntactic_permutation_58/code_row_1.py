from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")

def login(users, username, password):
    for user in users:
        if user.username == username and user.password == password:
            return user
    return None

def main():
    users = [User("john_doe", "john@example.com", "password123")]
    
    print("Login")
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")
    
    logged_in_user = login(users, username, password)
    
    if logged_in_user:
        print(f"Welcome {logged_in_user.username}!")
        
        old_email = input("Enter your current email: ")
        new_email = input("Enter the new email: ")
        confirm_password = getpass("Confirm your password: ")
        
        logged_in_user.change_email(old_email, new_email, confirm_password)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()