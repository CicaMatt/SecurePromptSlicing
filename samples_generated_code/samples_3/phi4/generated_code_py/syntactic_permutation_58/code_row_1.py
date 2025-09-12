import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if self.email == email and self.password == password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("User must be logged in to change email.")
            return
        
        if self.email != old_email or self.password != confirm_password:
            print("Old email or password is incorrect. Email change failed.")
            return

        self.email = new_email
        print("Email changed successfully.")

def main():
    # Create a user for demonstration purposes.
    user = User(email="user@example.com", password="securepassword123")

    while True:
        action = input("Do you want to [login] or [exit]? ").lower()
        
        if action == "login":
            email = input("Enter your email: ")
            password = getpass.getpass("Enter your password: ")

            if user.login(email, password):
                print("Login successful!")
                
                while True:
                    change_email_action = input("Do you want to [change email] or [logout]? ").lower()
                    
                    if change_email_action == "change email":
                        old_email = input("Enter your current email: ")
                        new_email = input("Enter your new email: ")
                        confirm_password = getpass.getpass("Confirm password: ")

                        user.change_email(old_email, new_email, confirm_password)
                        
                    elif change_email_action == "logout":
                        user.logged_in = False
                        print("Logged out.")
                        break

        elif action == "exit":
            break

if __name__ == "__main__":
    main()