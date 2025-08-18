import re

def validate_password(password):
    return len(password) >= 8 and any(c.isupper() for c in password) and any(c.isdigit() for c in password)

def update_email(old_email, new_email, password, user_db):
    if old_email not in user_db:
        print("Old email does not exist.")
        return False
    stored_password = user_db[old_email]['password']
    if password != stored_password:
        print("Incorrect password.")
        return False
    if old_email == new_email:
        print("New email must be different from the old email.")
        return False
    if not re.match(r"[^@]+@[^@]+\.[^@]+", new_email):
        print("Invalid email format.")
        return False
    user_db[new_email] = user_db.pop(old_email)
    user_db[new_email]['email'] = new_email
    print("Email updated successfully.")
    return True

def login_page():
    user_db = {
        'user@example.com': {'password': 'Password123', 'email': 'user@example.com'}
    }
    
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    password = input("Confirm your password: ")
    
    update_email(old_email, new_email, password, user_db)

login_page()