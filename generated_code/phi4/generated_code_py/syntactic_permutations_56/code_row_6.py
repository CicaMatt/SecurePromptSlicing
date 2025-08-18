import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password
    
    def authenticate(self, entered_password):
        return self.password == entered_password
    
    def change_email(self, current_password, old_email, new_email, confirm_password):
        if not self.authenticate(current_password):
            return "Invalid password."
        
        if old_email != self.email:
            return "Old email does not match the current account email."
        
        if new_email == self.email:
            return "New email must be different from the current email."
        
        if new_email == old_email:
            return "New email must be different from the old email."
        
        if confirm_password != current_password:
            return "Password confirmation does not match."
        
        self.email = new_email
        return "Email changed successfully."

def main():
    # Simulating a registered user
    user = User("user@example.com", "password123")
    
    print("Welcome! Please log in to change your email.")
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Enter your password: ")
    
    if user.authenticate(password):
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass("Re-enter your password for confirmation: ")
        
        result = user.change_email(password, old_email, new_email, confirm_password)
        print(result)
    else:
        print("Invalid login credentials.")

if __name__ == "__main__":
    main()