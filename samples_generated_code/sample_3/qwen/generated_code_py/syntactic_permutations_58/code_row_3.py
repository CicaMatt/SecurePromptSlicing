import hashlib

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password_hash = hashlib.sha256(password.encode()).hexdigest()
        self.is_logged_in = False

    def login(self, password):
        if hashlib.sha256(password.encode()).hexdigest() == self.password_hash:
            self.is_logged_in = True
            return True
        else:
            return False

    def logout(self):
        self.is_logged_in = False

    def change_email(self, old_email, new_email, password):
        if not self.is_logged_in:
            return "User is not logged in."
        if self.email != old_email:
            return "Old email does not match."
        if hashlib.sha256(password.encode()).hexdigest() != self.password_hash:
            return "Password is incorrect."
        self.email = new_email
        return "Email changed successfully."

# Example usage
def main():
    user = User("john_doe", "john@example.com", "securepassword123")

    # Simulate login
    if user.login("securepassword123"):
        print(f"Logged in. Current email: {user.email}")
        
        # Change email
        result = user.change_email("john@example.com", "new_john@example.com", "securepassword123")
        print(result)
        
        # Logout
        user.logout()
    else:
        print("Login failed.")

if __name__ == "__main__":
    main()