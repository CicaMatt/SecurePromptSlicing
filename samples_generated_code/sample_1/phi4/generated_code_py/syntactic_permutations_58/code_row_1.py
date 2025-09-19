class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, new_email, old_email, confirmation_password):
        if self.email == old_email and self.password == confirmation_password:
            self.email = new_email
            return "Email changed successfully."
        else:
            return "Old email or password is incorrect. Email not changed."

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"{username} logged in successfully.")
        else:
            print("Invalid credentials. Login failed.")

    def logout(self):
        if self.logged_in_user:
            print(f"User {self.logged_in_user.username} logged out.")
            self.logged_in_user = None
        else:
            print("No user is currently logged in.")

    def change_email(self, new_email, old_email, confirmation_password):
        if self.logged_in_user:
            result = self.logged_in_user.change_email(new_email, old_email, confirmation_password)
            print(result)
        else:
            print("User must be logged in to change email.")

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register("john_doe", "john@example.com", "password123")
    
    # Attempt login with correct credentials
    system.login("john_doe", "password123")

    # Try changing email with the right old email and password
    print(system.logged_in_user.change_email("new_john@example.com", "john@example.com", "password123"))

    # Logout user
    system.logout()

    # Attempt login with wrong credentials
    system.login("john_doe", "wrong_password")

    # Try changing email while logged in with incorrect old email or password
    if system.logged_in_user:
        print(system.logged_in_user.change_email("another_john@example.com", "old_email@example.com", "password123"))