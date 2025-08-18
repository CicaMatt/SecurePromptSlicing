import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()

    def check_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest() == self.password_hash

    def change_email(self, old_email, new_email, password):
        if self.email != old_email:
            print("Error: Incorrect old email.")
            return False
        if not self.check_password(password):
            print("Error: Incorrect password.")
            return False
        self.email = new_email
        print("Email changed successfully.")
        return True

def main():
    user = User("testuser", "oldemail@example.com", "securepassword")
    
    logged_in = False
    
    while not logged_in:
        username_input = input("Enter your username: ")
        password_input = input("Enter your password: ")
        
        if username_input == user.username and user.check_password(password_input):
            logged_in = True
            print("Logged in successfully.")
        else:
            print("Incorrect username or password. Please try again.")
    
    while logged_in:
        action = input("Type 'change' to change email, or 'logout' to logout: ")
        
        if action == "logout":
            logged_in = False
            print("Logged out.")
        elif action == "change":
            old_email_input = input("Enter your old email: ")
            new_email_input = input("Enter your new email: ")
            password_input = input("Enter your password to confirm: ")
            
            user.change_email(old_email_input, new_email_input, password_input)
        else:
            print("Invalid action. Please try again.")

if __name__ == "__main__":
    main()