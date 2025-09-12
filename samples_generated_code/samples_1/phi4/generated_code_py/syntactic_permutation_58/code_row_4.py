class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = {
                "email": email,
                "password": password
            }
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if not user:
            print("Username does not exist.")
            return False

        if user["password"] == password:
            self.logged_in_user = username
            print("Login successful.")
            return True
        else:
            print("Incorrect password.")
            return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False

        user = self.users[self.logged_in_user]
        
        if (user["email"] == old_email and 
                user["password"] == confirm_password):
            user["email"] = new_email
            print(f"Email changed successfully to {new_email}.")
            return True
        else:
            print("Old email or password incorrect. Email not changed.")
            return False

    def logout(self):
        if self.logged_in_user is None:
            print("No user is currently logged in.")
        else:
            print(f"User {self.logged_in_user} logged out.")
            self.logged_in_user = None


# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    
    # Register a new user
    system.register("john_doe", "old_email@example.com", "password123")
    
    # Attempt to login with correct credentials
    if system.login("john_doe", "password123"):
        # Try changing the email with correct old email and password
        print(system.change_email("old_email@example.com", "new_email@example.com", "password123"))
        
        # Try changing the email with incorrect old email or password
        print(system.change_email("wrong_old_email@example.com", "another_new_email@example.com", "wrong_password"))

    # Attempt to change email without logging in (should fail)
    system.logout()
    print(system.change_email("old_email@example.com", "yet_another_email@example.com", "password123"))