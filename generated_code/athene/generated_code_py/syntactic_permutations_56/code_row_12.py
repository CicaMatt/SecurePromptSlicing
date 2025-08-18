from getpass import getpass

class LoginPage:
    def __init__(self):
        self.users = {
            "user1@example.com": "password1",
            "user2@example.com": "password2"
        }

    def login(self):
        email = input("Enter your email: ")
        password = getpass("Enter your password: ")

        if email in self.users and self.users[email] == password:
            print("Login successful!")
            self.update_email(email)
        else:
            print("Invalid credentials!")

    def update_email(self, old_email):
        while True:
            new_email = input("Enter your new email: ")
            if new_email == old_email:
                print("New email cannot be the same as the old one.")
                continue

            confirm_password = getpass("Confirm your password to update email: ")
            if self.users[old_email] == confirm_password:
                self.users[new_email] = self.users.pop(old_email)
                print(f"Email updated successfully! New email is {new_email}")
                break
            else:
                print("Incorrect password, cannot update email.")

if __name__ == "__main__":
    login_page = LoginPage()
    login_page.login()