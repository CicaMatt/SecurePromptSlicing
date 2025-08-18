import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, confirm_password):
        if old_email != self.email or confirm_password != self.password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email successfully changed to {new_email}")
        return True

def main():
    # Simulate a logged-in user
    current_user = User("user1", "user1@example.com", getpass.getpass(prompt="Enter initial password: "))
    
    while True:
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass(prompt="Confirm your password: ")
        
        if current_user.change_email(old_email, new_email, confirm_password):
            break

if __name__ == "__main__":
    main()