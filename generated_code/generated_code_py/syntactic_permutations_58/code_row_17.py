import hashlib

users = {}

def register(email, name):
    users[email] = {'name': name, 'password': '', 'logged_in': False}

def login(email, password):
    if email not in users:
        return False
    users[email]['logged_in'] = True
    return True

def logout(email):
    if email not in users:
        return False
    users[email]['logged_in'] = False
    return True

def change_password(email, old_password, new_password):
    if email not in users or not users[email]['logged_in']:
        return False
    users[email]['password'] = hashlib.sha256(new_password).hexdigest()
    return True

def change_email(email, old_email, password):
    if email not in users or not users[email]['logged_in']:
        return False
    if hashlib.sha256(password).hexdigest() != users[old_email]['password']:
        return False
    new_email = input('Enter your new email address: ')
    users[new_email] = {'name': users[old_email]['name'], 'password': users[old_email]['password'], 'logged_in': True}
    del users[old_email]
    return True