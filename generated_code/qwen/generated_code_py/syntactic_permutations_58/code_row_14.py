import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def login(user, entered_password):
    return user.password == entered_password

def change_email(user, old_email, new_email, entered_password):
    if not login(user, entered_password):
        print("Incorrect password.")
        return False
    if user.email != old_email:
        print("Old email does not match.")
        return False
    user.email = new_email
    print("Email changed successfully.")
    return True

def main():
    # Example user creation
    user = User(username="testuser", email="oldemail@example.com", password="securepassword")
    
    print("Login to change your email.")
    entered_password = getpass.getpass(prompt="Enter your password: ")
    
    if login(user, entered_password):
        old_email = input("Enter your old email: ")
        new_email = input("Enter your new email: ")
        change_email(user, old_email, new_email, entered_password)
    else:
        print("Login failed.")

if __name__ == "__main__":
    main()