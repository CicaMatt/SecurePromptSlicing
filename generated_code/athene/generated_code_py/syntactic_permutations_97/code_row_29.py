import hashlib

class RegistrationPage:
    def __init__(self):
        self.users = {}

    def hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def register(self, username, password, first_name, last_name, email):
        if username in self.users:
            return "Username already exists"
        
        hashed_password = self.hash_password(password)
        self.users[username] = {
            'password': hashed_password,
            'first_name': first_name,
            'last_name': last_name,
            'email': email
        }
        return "Registration succeeded"

# Example usage:
registration_page = RegistrationPage()
result = registration_page.register('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com')
print(result)