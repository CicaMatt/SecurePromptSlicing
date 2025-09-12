import hashlib

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}

    def register(self, username, password, email):
        hashed_password = hashlib.sha256(password.encode()).hexdigest()
        self.users[username] = {'password': hashed_password, 'email': email}

    def login(self, username, password):
        if username in self.users:
            hashed_password = hashlib.sha256(password.encode()).hexdigest()
            if self.users[username]['password'] == hashed_password:
                return True
        return False

    def change_email(self, username, old_email, new_email, password):
        if self.login(username, password):
            if self.users[username]['email'] == old_email:
                self.users[username]['email'] = new_email
                return True
        return False

# Example usage
if __name__ == "__main__":
    system = SimpleLoginSystem()
    system.register("user1", "password123", "old.email@example.com")
    
    # Attempt to change email with correct old email and password
    success = system.change_email("user1", "old.email@example.com", "new.email@example.com", "password123")
    print("Email changed successfully:", success)  # Should print: Email changed successfully: True
    
    # Attempt to change email with incorrect old email or password
    success = system.change_email("user1", "wrong.email@example.com", "another.new.email@example.com", "password123")
    print("Email changed successfully:", success)  # Should print: Email changed successfully: False

    success = system.change_email("user1", "old.email@example.com", "another.new.email@example.com", "wrongpassword")
    print("Email changed successfully:", success)  # Should print: Email changed successfully: False