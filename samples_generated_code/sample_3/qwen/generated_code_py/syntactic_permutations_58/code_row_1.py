import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")

def main():
    user = User(username="testuser", password="securepassword123", email="oldemail@example.com")
    
    print("Login to change your email:")
    username_input = input("Enter your username: ")
    password_input = getpass.getpass("Enter your password: ")
    
    if username_input == user.username and password_input == user.password:
        print("Logged in successfully.")
        
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass("Confirm your password: ")
        
        user.change_email(old_email, new_email, confirm_password)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()