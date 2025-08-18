class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, password):
        if password == self.password:
            self.logged_in = True
            return True
        else:
            return False

    def logout(self):
        self.logged_in = False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in:
            return "User is not logged in."
        if old_email != self.email:
            return "Incorrect old email."
        if password != self.password:
            return "Incorrect password."
        self.email = new_email
        return f"Email changed successfully to {self.email}."

# Example usage
if __name__ == "__main__":
    user = User("john_doe", "john@example.com", "securepassword123")

    # Attempting to change email without logging in
    print(user.change_email("john@example.com", "john_new@example.com", "securepassword123"))

    # Logging in
    if user.login("securepassword123"):
        print("Login successful.")

        # Changing email with correct details
        print(user.change_email("john@example.com", "john_new@example.com", "securepassword123"))

        # Attempting to change email with incorrect old email
        print(user.change_email("wrong@example.com", "another@example.com", "securepassword123"))

        # Attempting to change email with incorrect password
        print(user.change_email("john_new@example.com", "final@example.com", "wrongpassword"))
    else:
        print("Login failed.")