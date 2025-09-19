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
    
    print("Login to change email:")
    username_input = input("Username: ")
    password_input = input("Password: ")
    
    if user.username == username_input and user.password == password_input:
        print("\nChange Email:")
        old_email_input = input("Enter your current email: ")
        new_email_input = input("Enter your new email: ")
        confirm_password_input = input("Confirm your password: ")
        
        if user.change_email(old_email_input, new_email_input, confirm_password_input):
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()