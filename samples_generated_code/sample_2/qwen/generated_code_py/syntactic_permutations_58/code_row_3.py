import getpass

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

def main():
    user = User("testuser", "oldemail@example.com", "securepassword123")
    
    username_input = input("Enter your username: ")
    if username_input != user.username:
        print("Username not found.")
        return
    
    password_input = getpass.getpass("Enter your password: ")
    if password_input != user.password:
        print("Incorrect password.")
        return
    
    old_email_input = input("Enter your current email: ")
    new_email_input = input("Enter your new email: ")
    
    user.change_email(old_email_input, new_email_input, password_input)

if __name__ == "__main__":
    main()