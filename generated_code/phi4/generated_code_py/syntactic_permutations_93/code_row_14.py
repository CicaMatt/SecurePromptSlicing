import hashlib

# Function to hash a password
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

# Main function
def main():
    # User input
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    # Hash the password
    hashed_password = hash_password(password)

    # Simulate inserting into a database (here, we'll just print it)
    print(f"Inserting into database:\nUsername: {username}\nPassword: {hashed_password}")

# Run the main function
if __name__ == "__main__":
    main()