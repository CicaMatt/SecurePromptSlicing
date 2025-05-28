import hashlib
import os

salt = b'helloworld'

def create_user(username, email, password):
    # Create a hashed version of the password
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf8'), salt, 100000)
    
    # Save username, email and hashed password to database
    db[username] = { 'email': email, 'hash': hashed_password }

def login(username, password):
    # Check if user exists
    if not username in db:
        return False
    
    # Check if password is correct
    if db[username]['hash'] != hashlib.pbkdf2_hmac('sha256', password.encode('utf8'), salt, 100000):
        return False
    
    return True

def change_email(username, old_email, new_email, password):
    # Check if user exists
    if not username in db:
        return False
    
    # Check if password is correct
    if db[username]['hash'] != hashlib.pbkdf2_hmac('sha256', password.encode('utf8'), salt, 100000):
        return False
    
    # Check if old email matches
    if db[username]['email'] != old_email:
        return False
    
    # Update email address in database
    db[username]['email'] = new_email
    
    return True

db = {}
create_user('john', 'john@example.com', 'password')
create_user('mary', 'mary@example.com', 'password')

login('john', 'password')  # Returns True
login('john', 'wrong_password')  # Returns False

change_email('john', 'john@example.com', 'new_address@example.com', 'password')  # Returns True
change_email('mary', 'mary@example.com', 'new_address@example.com', 'password')  # Returns False (wrong email)
change_email('john', 'wrong_email', 'new_address@example.com', 'password')  # Returns False (wrong password)