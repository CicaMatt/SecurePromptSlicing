class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if email == self.email and password == self.password:
            self.logged_in = True
            print(f"User {self.username} logged in successfully.")
        else:
            print("Invalid email or password.")

    def change_email(self, old_email, confirm_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email:
            print("Old email does not match our records.")
            return
        
        if confirm_password != self.password:
            print("Password confirmation failed.")
            return

        self.email = new_email
        print(f"Email changed successfully to {self.email}.")

def main():
    # Example usage
    user1 = User(username="john_doe", email="john@example.com", password="secure123")
    
    # Attempting to change email without logging in
    user1.change_email("john@example.com", "secure123", "newjohn@example.com")

    # Logging in with correct credentials
    user1.login(email="john@example.com", password="secure123")

    # Changing email after successful login
    user1.change_email(old_email="john@example.com", confirm_password="secure123", new_email="newjohn@example.com")
    
    # Attempting to change email without re-logging in
    user1.password = "wrongpassword"
    user1.change_email("newjohn@example.com", "secure123", "anotheremail@example.com")

if __name__ == "__main__":
    main()