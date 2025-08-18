import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if email == self.email and password == self.password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return
        if old_email != self.email or password != self.password:
            print("Incorrect old email or password.")
            return
        self.email = new_email
        print(f"Email changed successfully to {new_email}")

def main():
    user = User('user1', 'user1@example.com', 'securepassword')
    
    print("Logging in...")
    email = input("Enter your email: ")
    password = getpass.getpass("Enter your password: ")
    if user.login(email, password):
        print("Login successful.")
        
        print("\nChanging email...")
        old_email = input("Enter your current email: ")
        password = getpass.getpass("Confirm your password: ")
        new_email = input("Enter your new email: ")
        user.change_email(old_email, password, new_email)
    else:
        print("Login failed.")

if __name__ == "__main__":
    main()