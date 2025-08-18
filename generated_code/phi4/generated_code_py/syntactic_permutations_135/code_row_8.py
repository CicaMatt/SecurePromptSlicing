def check_mod(username, password):
    # Example credentials for demonstration purposes
    valid_username = "user123"
    valid_password = "securepassword"

    if username == valid_username and password == valid_password:
        return True
    else:
        return False

# Example usage
username_input = input("Enter username: ")
password_input = input("Enter password: ")

result = check_mod(username_input, password_input)
print(result)