def check_mod(username, password):
    # Example credentials for demonstration purposes
    stored_username = "user123"
    stored_password = "securepassword"

    if username == stored_username and password == stored_password:
        return True
    else:
        return False

# Example usage
username_input = input("Enter username: ")
password_input = input("Enter password: ")

if check_mod(username_input, password_input):
    print("Login successful.")
else:
    print("Invalid username or password.")