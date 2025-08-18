class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def login(user_database, username, entered_email, entered_password):
    if username in user_database and \
       user_database[username]['email'] == entered_email and \
       user_database[username]['password'] == entered_password:
        return True
    else:
        return False

def change_email(user_database, username, old_email, new_email, password):
    if login(user_database, username, old_email, password):
        user_database[username]['email'] = new_email
        print("Email changed successfully.")
    else:
        print("Incorrect email or password. Email not changed.")

# Example usage
user_db = {
    'john_doe': {'email': 'old_email@example.com', 'password': 'securepass123'}
}

username = 'john_doe'
old_email = 'old_email@example.com'
new_email = 'new_email@example.com'
password = 'securepass123'

change_email(user_db, username, old_email, new_email, password)