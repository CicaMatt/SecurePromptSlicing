import getpass

class User:
    def __init__(self, username, email):
        self.username = username
        self.email = email

def change_email(user):
    old_email = input("Enter your current email: ").strip()
    if old_email != user.email:
        print("The provided email does not match the current email.")
        return
    
    new_email = input("Enter your new email: ").strip()
    confirm = getpass.getpass("Confirm by entering your password: ")

    # Simulating a password check
    correct_password = "password123"  # This should be stored securely in a real application
    if confirm != correct_password:
        print("Incorrect confirmation.")
        return
    
    user.email = new_email
    print(f"Email successfully changed to {new_email}")

def login():
    username = input("Enter your username: ").strip()
    email = input("Enter your email: ").strip()
    # Simulating a user lookup
    if not (username and email):
        print("Login failed. Invalid credentials.")
        return None
    return User(username, email)

def main():
    user = login()
    if user:
        change_email(user)
        print(f"Current Email: {user.email}")

if __name__ == "__main__":
    main()