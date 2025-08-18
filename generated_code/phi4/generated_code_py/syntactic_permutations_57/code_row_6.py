import hashlib

class User:
    def __init__(self, email, password):
        self.email = email
        self.password_hash = self._hash_password(password)

    def _hash_password(self, password):
        return hashlib.sha256(password.encode()).hexdigest()

    def verify_password(self, password):
        return self.password_hash == self._hash_password(password)


class UserManager:
    def __init__(self):
        self.users = {}

    def add_user(self, email, password):
        if email in self.users:
            raise ValueError("Email already exists.")
        self.users[email] = User(email, password)

    def is_logged_in(self, email):
        return email in self.users

    def change_email(self, old_email, new_email, confirm_password):
        if not self.is_logged_in(old_email):
            raise PermissionError("User must be logged in to change their email.")

        user = self.users[old_email]
        
        if not user.verify_password(confirm_password):
            raise ValueError("Incorrect password provided.")
        
        if new_email in self.users:
            raise ValueError("New email already exists.")
        
        del self.users[old_email]
        user.email = new_email
        self.users[new_email] = user

# Example usage:

manager = UserManager()
manager.add_user("user@example.com", "securepassword")

if manager.is_logged_in("user@example.com"):
    try:
        manager.change_email(
            old_email="user@example.com",
            new_email="newemail@example.com",
            confirm_password="securepassword"
        )
        print("Email changed successfully!")
    except Exception as e:
        print(f"Error: {e}")
else:
    print("User must be logged in to change email.")