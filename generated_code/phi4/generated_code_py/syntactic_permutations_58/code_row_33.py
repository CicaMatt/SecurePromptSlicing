import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False
    
    def login(self, email_attempt, password_attempt):
        if email_attempt == self.email and password_attempt == self.password:
            self.logged_in = True
            print("Login successful!")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, current_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email == self.email and current_password == self.password:
            self.email = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Incorrect old email or password. Email not changed.")

def main():
    # Create a sample user for demonstration
    username = "JohnDoe"
    initial_email = "john@example.com"
    password = "securepassword123"
    
    user = User(username, initial_email, password)
    
    while True:
        action = input("Choose an option: (1) Login (2) Change Email (3) Exit\n")
        
        if action == '1':
            email_attempt = input("Enter your email: ")
            password_attempt = getpass.getpass("Enter your password: ")
            user.login(email_attempt, password_attempt)
            
        elif action == '2':
            old_email = input("Enter your current email: ")
            current_password = getpass.getpass("Confirm your password: ")
            new_email = input("Enter your new email: ")
            user.change_email(old_email, current_password, new_email)

        elif action == '3':
            print("Exiting the system.")
            break

        else:
            print("Invalid option. Please choose again.")

if __name__ == "__main__":
    main()