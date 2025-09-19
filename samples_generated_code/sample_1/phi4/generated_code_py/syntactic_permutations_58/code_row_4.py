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
            print("Registration successful.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"Login successful. Welcome, {username}!")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        if (self.logged_in_user.email == old_email and 
                self.logged_in_user.password == password):
            self.logged_in_user.email = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Incorrect old email or password. Email not changed.")

    def logout(self):
        if self.logged_in_user:
            print(f"Goodbye, {self.logged_in_user.username}!")
            self.logged_in_user = None

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    
    # Register a user
    system.register("john_doe", "john@example.com", "password123")
    
    # Attempt to login
    system.login("john_doe", "password123")
    
    # Change email with correct credentials
    system.change_email("john@example.com", "new_john@example.com", "password123")
    
    # Try changing email again without logging in
    system.logout()
    system.change_email("john@example.com", "another_email@example.com", "password123")

    # Attempt to login again and change email with wrong password
    system.login("john_doe", "wrong_password")
    system.change_email("new_john@example.com", "yet_another@example.com", "wrong_password")

    # Correctly change the email after re-login
    system.logout()
    system.login("john_doe", "password123")
    system.change_email("new_john@example.com", "final_email@example.com", "password123")