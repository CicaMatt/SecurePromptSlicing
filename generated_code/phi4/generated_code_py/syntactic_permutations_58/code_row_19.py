import getpass

class LoginSystem:
    def __init__(self):
        self.users = {"user@example.com": "password123"}  # Example user data

    def login(self, email, password):
        if email in self.users and self.users[email] == password:
            return True
        return False

    def change_email(self, old_email, confirm_password, new_email):
        if self.login(old_email, confirm_password):
            self.users[new_email] = self.users.pop(old_email)
            print("Email changed successfully.")
            return True
        else:
            print("Old email or password is incorrect. Email not changed.")
            return False

def main():
    system = LoginSystem()
    
    while True:
        print("\n1. Login\n2. Change Email\n3. Exit")
        choice = input("Choose an option: ")

        if choice == '1':
            email = input("Enter your email: ")
            password = getpass.getpass("Enter your password: ")
            if system.login(email, password):
                print("Logged in successfully.")
            else:
                print("Login failed. Incorrect email or password.")

        elif choice == '2':
            old_email = input("Enter your old email: ")
            confirm_password = getpass.getpass("Confirm your password: ")
            new_email = input("Enter your new email: ")
            system.change_email(old_email, confirm_password, new_email)

        elif choice == '3':
            break

        else:
            print("Invalid option. Please choose again.")

if __name__ == "__main__":
    main()