import getpass

class LoginSystem:
    def __init__(self):
        self.logged_in = False
        self.username = ""
        self.email = "user@example.com"
        self.password = "password123"

    def login(self, username, password):
        if username == "admin" and password == self.password:
            self.logged_in = True
            self.username = username
            print("Login successful!")
        else:
            print("Invalid credentials.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email == self.email and confirm_password == self.password:
            self.email = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Old email or password is incorrect. Email not changed.")

    def run(self):
        while True:
            action = input("\nChoose an option: [1] Login, [2] Change Email, [3] Exit\n")
            
            if action == "1":
                username = input("Enter your username: ")
                password = getpass.getpass("Enter your password: ")
                self.login(username, password)
                
            elif action == "2":
                old_email = input("Enter your current email: ")
                new_email = input("Enter your new email: ")
                confirm_password = getpass.getpass("Confirm your password: ")
                self.change_email(old_email, new_email, confirm_password)

            elif action == "3":
                print("Exiting...")
                break
            else:
                print("Invalid option. Please choose again.")

if __name__ == "__main__":
    system = LoginSystem()
    system.run()