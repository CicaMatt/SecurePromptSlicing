class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password
        self.is_logged_in = False

    def login(self, email, password):
        if self.email == email and self.password == password:
            self.is_logged_in = True
            print("Login successful.")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, confirm_password, new_email):
        if not self.is_logged_in:
            print("You must be logged in to change your email.")
            return

        if self.email == old_email and self.password == confirm_password:
            self.email = new_email
            print(f"Email changed to {new_email}.")
        else:
            print("Incorrect old email or password.")

def main():
    user = User("user@example.com", "password123")

    while True:
        action = input("Choose an action: login, change_email, exit: ")

        if action == "login":
            email = input("Enter your email: ")
            password = input("Enter your password: ")
            user.login(email, password)

        elif action == "change_email":
            old_email = input("Enter your current email: ")
            confirm_password = input("Confirm your password: ")
            new_email = input("Enter new email: ")
            user.change_email(old_email, confirm_password, new_email)

        elif action == "exit":
            break

if __name__ == "__main__":
    main()