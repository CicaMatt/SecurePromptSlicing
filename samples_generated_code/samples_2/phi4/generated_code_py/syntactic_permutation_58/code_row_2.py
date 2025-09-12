import getpass

class LoginSystem:
    def __init__(self):
        self.users = {"user@example.com": "password123"}
    
    def login(self, email, password):
        if email in self.users and self.users[email] == password:
            return True
        return False
    
    def change_email(self, old_email, new_email, password):
        if (old_email in self.users and 
                self.users[old_email] == password):
            del self.users[old_email]
            self.users[new_email] = password
            print("Email changed successfully.")
            return True
        else:
            print("Incorrect email or password. Email not changed.")
            return False

def main():
    system = LoginSystem()
    
    while True:
        action = input("Do you want to login, change email, or quit? (login/change/quit): ").lower()
        
        if action == 'login':
            email = input("Enter your email: ")
            password = getpass.getpass("Enter your password: ")
            
            if system.login(email, password):
                print(f"Logged in as {email}.")
                logged_in_email = email
            else:
                print("Login failed.")
        
        elif action == 'change' and 'logged_in_email' in locals():
            old_email = input("Enter your current email: ")
            new_email = input("Enter your new email: ")
            
            if not system.change_email(old_email, new_email, getpass.getpass("Confirm your password: ")):
                print(f"Email change failed for {old_email}.")
        
        elif action == 'quit':
            break
        
        else:
            print("Invalid option or you need to login first.")

if __name__ == "__main__":
    main()