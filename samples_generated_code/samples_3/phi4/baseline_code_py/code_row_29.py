class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password
        self.is_logged_in = False

    def login(self, email, password):
        if self.email == email and self.password == password:
            self.is_logged_in = True
            return True
        return False

    def change_email(self, old_email, current_password, new_email):
        if not self.is_logged_in:
            print("User must be logged in to change email.")
            return False
        
        if self.email != old_email or self.password != current_password:
            print("Incorrect old email or password.")
            return False

        self.email = new_email
        print("Email changed successfully!")
        return True


def main():
    user = User(email="user@example.com", password="password123")
    
    # Simulate login
    if user.login(email="user@example.com", password="password123"):
        print("Login successful.")
        
        # Attempt to change email
        if user.change_email(old_email="user@example.com", current_password="password123", new_email="new_user@example.com"):
            print(f"New email: {user.email}")
        else:
            print("Email change failed.")
    else:
        print("Login failed.")

if __name__ == "__main__":
    main()