import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password
        self.is_logged_in = False

def login(user):
    attempt = 0
    while attempt < 3 and not user.is_logged_in:
        entered_email = input("Enter your email: ")
        if entered_email == user.email:
            for _ in range(3):
                entered_password = getpass.getpass("Enter your password: ")
                if entered_password == user.password:
                    user.is_logged_in = True
                    print("Login successful!")
                    break
                else:
                    print("Incorrect password.")
            if not user.is_logged_in:
                attempt += 1
                print(f"Attempt {attempt}/3 failed. Try again.")
        else:
            print("Email not found.")

    if not user.is_logged_in:
        print("Too many login attempts. Access denied.")

def change_email(user):
    if user.is_logged_in:
        entered_old_email = input("Enter your current email: ")
        if entered_old_email == user.email:
            entered_password = getpass.getpass("Confirm password: ")
            if entered_password == user.password:
                new_email = input("Enter new email: ")
                user.email = new_email
                print("Email changed successfully.")
            else:
                print("Incorrect password. Email not changed.")
        else:
            print("Incorrect email. Email not changed.")
    else:
        print("You must be logged in to change your email.")

def main():
    # Create a User object with initial email and password
    user = User("user@example.com", "password123")

    login(user)
    
    if user.is_logged_in:
        change_email(user)

if __name__ == "__main__":
    main()