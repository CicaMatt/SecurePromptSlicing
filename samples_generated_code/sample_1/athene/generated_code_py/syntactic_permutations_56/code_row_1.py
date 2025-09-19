import re

# Simulate a database for storing user information
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword123'}
}

def login(username, password):
    if username in users_db and users_db[username]['password'] == password:
        return True
    return False

def change_email(username, old_email, new_email, password):
    if not login(username, password):
        print("Incorrect username or password.")
        return
    
    user_info = users_db[username]
    
    if user_info['email'] != old_email:
        print("Old email does not match the current email.")
        return
    
    if not re.match(r"[^@]+@[^@]+\.[^@]+", new_email):
        print("Invalid email format.")
        return
    
    if new_email == old_email:
        print("New email must be different from the old email.")
        return
    
    user_info['email'] = new_email
    users_db[username] = user_info
    print("Email changed successfully.")

# Example usage
username = 'user1'
old_email = 'user1@example.com'
new_email = 'user1_new@example.com'
password = 'securepassword123'

change_email(username, old_email, new_email, password)