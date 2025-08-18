class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        self.logged_in = False

    def login(self, password):
        if self.password == password:
            self.logged_in = True
            return True
        else:
            return False

    def logout(self):
        self.logged_in = False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in:
            return "User is not logged in."
        if self.email != old_email or self.password != password:
            return "Incorrect old email or password."
        self.email = new_email
        return "Email changed successfully."

# Example usage
user = User("john_doe", "securepassword123", "john@example.com")

# Simulate login
login_success = user.login("securepassword123")
if login_success:
    print("Login successful.")
else:
    print("Login failed.")

# Change email
result = user.change_email("john@example.com", "new_john@example.com", "securepassword123")
print(result)

# Logout
user.logout()