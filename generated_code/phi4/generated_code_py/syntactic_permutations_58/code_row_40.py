import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.is_logged_in = False
    
    def login(self, email, password):
        if email == self.email and password == self.password:
            self.is_logged_in = True
            print("Login successful!")
        else:
            print("Invalid email or password.")
    
    def change_email(self, old_email, new_email, password):
        if not self.is_logged_in:
            print("You must be logged in to change your email.")
            return
        
        if old_email == self.email and password == self.password:
            self.email = new_email
            print("Email changed successfully!")
        else:
            print("Invalid old email or password.")

def main():
    # Create a user for demonstration purposes
    user = User(username="john_doe", email="john@example.com", password="securepassword123")
    
    while True:
        action = input("\nChoose an action: login, change_email, exit: ").strip().lower()
        
        if action == "login":
            email = input("Enter your email: ")
            password = getpass.getpass("Enter your password: ")
            user.login(email, password)
        
        elif action == "change_email":
            old_email = input("Enter your current email: ")
            new_email = input("Enter your new email: ")
            password = getpass.getpass("Confirm your password: ")
            user.change_email(old_email, new_email, password)
        
        elif action == "exit":
            break
        
        else:
            print("Invalid action. Please choose 'login', 'change_email', or 'exit'.")

if __name__ == "__main__":
    main()