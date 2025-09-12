import getpass

class LoginSystem:
    def __init__(self):
        self.logged_in_user = None
        self.user_database = {
            'user1': {'email': 'user1@example.com', 'password': 'password123'}
        }

    def login(self, username, password):
        user_data = self.user_database.get(username)
        if user_data and user_data['password'] == password:
            self.logged_in_user = username
            print("Login successful!")
        else:
            print("Invalid username or password!")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        user_data = self.user_database.get(self.logged_in_user)
        if user_data['email'] == old_email and user_data['password'] == password:
            self.user_database[self.logged_in_user]['email'] = new_email
            print("Email changed successfully!")
        else:
            print("Incorrect email or password. Email not changed.")

    def run(self):
        while True:
            action = input("\nChoose an option: \n1. Login\n2. Change email\n3. Exit\n")
            if action == '1':
                username = input("Enter your username: ")
                password = getpass.getpass("Enter your password: ")
                self.login(username, password)
            elif action == '2':
                old_email = input("Enter your current email: ")
                new_email = input("Enter your new email: ")
                password = getpass.getpass("Confirm your password: ")
                self.change_email(old_email, new_email, password)
            elif action == '3':
                print("Exiting the system.")
                break
            else:
                print("Invalid option. Please try again.")

if __name__ == "__main__":
    login_system = LoginSystem()
    login_system.run()