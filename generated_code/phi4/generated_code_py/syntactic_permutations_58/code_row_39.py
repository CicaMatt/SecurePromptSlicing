class LoginSystem:
    def __init__(self):
        self.users = {
            'user@example.com': {'password': 'password123', 'logged_in': False}
        }

    def login(self, email, password):
        if email in self.users and self.users[email]['password'] == password:
            self.users[email]['logged_in'] = True
            print("Login successful.")
            return True
        print("Invalid email or password.")
        return False

    def logout(self, email):
        if email in self.users:
            self.users[email]['logged_in'] = False
            print("Logout successful.")

    def change_email(self, old_email, new_email, password):
        if (old_email in self.users and 
                self.users[old_email]['password'] == password and 
                self.users[old_email]['logged_in']):
            
            if new_email not in self.users:
                del self.users[old_email]
                self.users[new_email] = {'password': self.users[old_email]['password'], 'logged_in': True}
                print(f"Email changed to {new_email}.")
            else:
                print("New email already exists.")
        else:
            print("Invalid old email, password, or not logged in.")

def main():
    system = LoginSystem()

    # Simulate login
    if system.login('user@example.com', 'password123'):
        
        # Attempt to change email
        system.change_email('user@example.com', 'newemail@example.com', 'password123')

        # Logout
        system.logout('newemail@example.com')

if __name__ == "__main__":
    main()