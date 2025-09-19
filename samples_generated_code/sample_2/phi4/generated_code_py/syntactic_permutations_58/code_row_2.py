class LoginSystem:
    def __init__(self):
        self.users = {}
    
    def register(self, email, password):
        if email in self.users:
            print("Email already exists.")
        else:
            self.users[email] = {'password': password}
            print(f"User with email {email} registered successfully.")
    
    def login(self, email, password):
        if email in self.users and self.users[email]['password'] == password:
            return True
        return False
    
    def change_email(self, old_email, new_email, password):
        if old_email not in self.users or self.users[old_email]['password'] != password:
            print("Incorrect email or password.")
            return
        
        if new_email in self.users:
            print("New email already exists.")
            return
        
        self.users[new_email] = self.users.pop(old_email)
        print(f"Email changed to {new_email}.")

def main():
    system = LoginSystem()
    
    while True:
        action = input("Choose an action: register, login, change_email, or quit: ").strip().lower()

        if action == "register":
            email = input("Enter email for registration: ")
            password = input("Enter password: ")
            system.register(email, password)

        elif action == "login":
            email = input("Enter your email: ")
            password = input("Enter your password: ")
            if system.login(email, password):
                print("Login successful.")
            else:
                print("Invalid credentials.")

        elif action == "change_email":
            if not system.login(input("Enter current email: "), input("Enter your password: ")):
                print("You must be logged in to change your email.")
                continue

            old_email = input("Enter current email: ")
            new_email = input("Enter new email: ")
            password = input("Confirm your password: ")
            system.change_email(old_email, new_email, password)

        elif action == "quit":
            break
        
        else:
            print("Invalid action.")

if __name__ == "__main__":
    main()