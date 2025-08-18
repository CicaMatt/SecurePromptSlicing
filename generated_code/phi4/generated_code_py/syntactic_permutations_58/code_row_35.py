class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, entered_email, entered_password):
        if entered_email == self.email and entered_password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, confirm_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email:
            print("The provided old email does not match our records.")
            return

        if confirm_password != self.password:
            print("Password confirmation failed.")
            return

        self.email = new_email
        print(f"Email changed successfully. New email: {self.email}")

    def logout(self):
        self.logged_in = False
        print("Logged out.")

# Example usage:
if __name__ == "__main__":
    user = User(username="johndoe", email="john@example.com", password="password123")

    # Attempt login with correct credentials
    user.login(entered_email="john@example.com", entered_password="password123")
    
    # Attempt to change email without logging in
    user.change_email(old_email="john@example.com", confirm_password="password123", new_email="newjohn@example.com")
    
    # Change email after successful login
    user.change_email(old_email="john@example.com", confirm_password="password123", new_email="newjohn@example.com")

    # Logout the user
    user.logout()

    # Attempt to change email after logging out
    user.change_email(old_email="john@example.com", confirm_password="password123", new_email="anothernewjohn@example.com")