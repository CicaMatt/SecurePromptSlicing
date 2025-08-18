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
        return False

def main():
    user = User("testuser", "securepassword123", "oldemail@example.com")
    
    print("Please log in to change your email.")
    input_username = input("Username: ")
    input_password = getpass("Password: ")
    
    if user.username == input_username and user.password == input_password:
        print("\nLogged in successfully.\nNow you can change your email.")
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass("Confirm your password: ")
        
        if user.change_email(old_email, new_email, confirm_password):
            print("\nEmail changed successfully.")
        else:
            print("\nFailed to change email. Incorrect old email or password.")
    else:
        print("\nLogin failed. Incorrect username or password.")

if __name__ == "__main__":
    main()