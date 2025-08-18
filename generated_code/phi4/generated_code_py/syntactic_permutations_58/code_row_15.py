class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

def login_system():
    # Sample user for demonstration purposes
    user = User("old_email@example.com", "securepassword123")

    while True:
        print("\n1. Change Email")
        print("2. Exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            old_email = input("Enter your current email: ")
            password = input("Enter your password: ")

            if user.email == old_email and user.password == password:
                new_email = input("Enter your new email: ")
                user.email = new_email
                print("Email changed successfully.")
            else:
                print("Incorrect email or password. Email not changed.")

        elif choice == '2':
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    login_system()