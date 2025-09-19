from getpass import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            return True
        else:
            return False

def main():
    user = User("testuser", "securepassword123", "oldemail@example.com")
    
    print("Login to change your email:")
    username_input = input("Username: ")
    password_input = getpass("Password: ")

    if username_input == user.username and password_input == user.password:
        print("Logged in successfully.")
        
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass("Confirm your password: ")

        if user.change_email(old_email, new_email, confirm_password):
            print(f"Email changed successfully. New email: {user.email}")
        else:
            print("Failed to change email. Incorrect old email or password.")
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()