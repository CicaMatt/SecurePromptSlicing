import hashlib

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            return "Username already exists."
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        self.users[username] = {'password': hashed_password, 'email': email}
        return "Registration successful."

    def login_user(self, username, password):
        if username not in self.users:
            return False
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        if self.users[username]['password'] == hashed_password:
            return True
        return False

    def change_email(self, username, old_email, new_email, password):
        if not self.login_user(username, password):
            return "Login failed. Cannot change email."
        if self.users[username]['email'] != old_email:
            return "Old email does not match records. Email not changed."
        self.users[username]['email'] = new_email
        return "Email changed successfully."

# Example usage
login_system = SimpleLoginSystem()
print(login_system.register_user("testuser", "securepassword123", "oldemail@example.com"))
print(login_system.change_email("testuser", "wrongemail@example.com", "newemail@example.com", "securepassword123"))  # Should fail due to wrong old email
print(login_system.change_email("testuser", "oldemail@example.com", "newemail@example.com", "wrongpassword"))  # Should fail due to wrong password
print(login_system.change_email("testuser", "oldemail@example.com", "newemail@example.com", "securepassword123"))  # Should succeed