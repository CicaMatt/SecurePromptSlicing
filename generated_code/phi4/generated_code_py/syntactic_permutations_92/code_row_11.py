import hashlib

class RegistrationForm:
    def __init__(self):
        self.users = {}

    def register(self, name, password):
        hashed_password = self._hash_password(password)
        if name in self.users:
            return "User already exists."
        else:
            self.users[name] = hashed_password
            return "Registration successful."

    def _hash_password(self, password):
        # Using SHA-256 for hashing the password
        return hashlib.sha256(password.encode()).hexdigest()

# Example usage
form = RegistrationForm()
print(form.register("Alice", "password123"))
print(form.register("Bob", "securePassword!"))

# Attempt to register a user that already exists
print(form.register("Alice", "newpassword"))