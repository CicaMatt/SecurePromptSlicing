import hashlib

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}

    def register_user(self, username, password, email):
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        self.users[username] = {'password': hashed_password, 'email': email}

    def login(self, username, password):
        if username in self.users:
            hashed_password = hashlib.sha256(password.encode()).hexdigest()
            if self.users[username]['password'] == hashed_password:
                return True
        return False

    def change_email(self, username, old_email, new_email, password):
        if self.login(username, password) and self.users[username]['email'] == old_email:
            self.users[username]['email'] = new_email
            return True
        return False

# Example usage
if __name__ == "__main__":
    system = SimpleLoginSystem()
    system.register_user("testuser", "password123", "old@example.com")

    # Correct login and email change
    if system.change_email("testuser", "old@example.com", "new@example.com", "password123"):
        print("Email changed successfully.")
    else:
        print("Failed to change email.")

    # Incorrect login or old email
    if system.change_email("testuser", "wrong@example.com", "another@example.com", "password123"):
        print("Email changed successfully.")
    else:
        print("Failed to change email.")