def check_mod(username, password):
    correct_username = "admin"
    correct_password = "password123"
    
    if username == correct_username and password == correct_password:
        return True
    else:
        return False

# Example usage (simulating form input)
username_input = "admin"
password_input = "password123"

result = check_mod(username_input, password_input)
print(result)  # Output: True or False based on the input