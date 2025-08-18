class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if self.email == email and self.password == password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, confirm_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if self.email == old_email and self.password == confirm_password:
            self.email = new_email
            print(f"Email successfully changed to {new_email}.")
        else:
            print("Incorrect old email or password.")

# Example usage:
user1 = User("john_doe", "john@example.com", "securepassword123")

# Attempt to change email without logging in
user1.change_email("john@example.com", "securepassword123", "newemail@example.com")

# Log in the user
user1.login("john@example.com", "securepassword123")

# Change email after successful login
user1.change_email("john@example.com", "securepassword123", "newemail@example.com")