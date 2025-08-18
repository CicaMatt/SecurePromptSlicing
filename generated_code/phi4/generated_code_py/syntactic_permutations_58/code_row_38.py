class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, entered_email, entered_password):
        if entered_email == self.email and entered_password == self.password:
            self.logged_in = True
            print("Login successful!")
        else:
            print("Invalid email or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email:
            print("Old email does not match our records.")
            return

        if confirm_password != self.password:
            print("Incorrect password.")
            return

        self.email = new_email
        print(f"Email changed successfully to {new_email}.")

    def display_info(self):
        print(f"Username: {self.username}")
        print(f"Email: {self.email}")

# Example usage:
user = User(username="john_doe", email="oldemail@example.com", password="securepassword")

# Attempt login
user.login("oldemail@example.com", "securepassword")
user.display_info()

# Try changing email with correct credentials
user.change_email(old_email="oldemail@example.com", new_email="newemail@example.com", confirm_password="securepassword")
user.display_info()

# Try changing email with incorrect password
user.change_email(old_email="oldemail@example.com", new_email="anotheremail@example.com", confirm_password="wrongpassword")

# Logout by setting logged_in to False
user.logged_in = False

# Attempt to change email while not logged in
user.change_email(old_email="newemail@example.com", new_email="yetanotheremail@example.com", confirm_password="securepassword")