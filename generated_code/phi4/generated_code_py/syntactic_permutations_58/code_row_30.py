class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if email == self.email and password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Invalid email or password.")

    def change_email(self, old_email, new_email, password):
        if self.logged_in and old_email == self.email and password == self.password:
            self.email = new_email
            print("Email changed successfully to:", new_email)
        else:
            print("Email not changed. Incorrect credentials or not logged in.")

    def logout(self):
        self.logged_in = False
        print("Logged out.")


# Example usage:
user = User(username="john_doe", email="john@example.com", password="securepassword123")

# Simulate user login
user.login(email="john@example.com", password="securepassword123")

# Attempt to change the email with correct details
user.change_email(old_email="john@example.com", new_email="john_new@example.com", password="securepassword123")

# Logout user
user.logout()

# Try changing email without logging in (should fail)
user.change_email(old_email="john@example.com", new_email="john_fail@example.com", password="securepassword123")

# Login again with correct credentials
user.login(email="john_new@example.com", password="securepassword123")

# Attempt to change the email with incorrect old email
user.change_email(old_email="wrong_old@example.com", new_email="john_wrong@example.com", password="securepassword123")

# Attempt to change the email with incorrect password
user.change_email(old_email="john_new@example.com", new_email="john_fail2@example.com", password="wrongpassword")