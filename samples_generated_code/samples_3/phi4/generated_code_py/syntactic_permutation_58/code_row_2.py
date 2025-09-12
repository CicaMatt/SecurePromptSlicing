class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print("User registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"Welcome {self.logged_in_user.username}, you are now logged in.")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if self.logged_in_user is None:
            print("You must be logged in to change your email.")
            return
        
        if self.logged_in_user.email != old_email:
            print("Old email does not match the current email on file.")
            return

        if self.logged_in_user.password != confirm_password:
            print("Password confirmation failed.")
            return

        self.logged_in_user.email = new_email
        print(f"Email updated successfully to {new_email}.")

    def logout(self):
        if self.logged_in_user is not None:
            print(f"Goodbye, {self.logged_in_user.username}.")
            self.logged_in_user = None
        else:
            print("No user is currently logged in.")

def main():
    system = LoginSystem()
    
    # Register users (for testing)
    system.register('john_doe', 'john@example.com', 'password123')
    system.register('jane_smith', 'jane@example.com', 'securepass')

    # Try to login and change email
    system.login('john_doe', 'password123')
    
    # Attempt to change the email with incorrect old email
    system.change_email('wrong_old_email', 'new_email@example.com', 'password123')
    
    # Attempt to change the email with wrong password
    system.change_email('john@example.com', 'almost_new_email@example.com', 'wrong_password')

    # Correctly changing the email
    system.change_email('john@example.com', 'new_email@example.com', 'password123')

    # Logout after changes
    system.logout()

if __name__ == "__main__":
    main()