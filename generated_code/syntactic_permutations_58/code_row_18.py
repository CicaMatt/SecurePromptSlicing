import hashlib

users = {
    "bob": hashlib.sha256("secretpassword".encode()).hexdigest()
}

def login(username, password):
    if username in users and hashlib.sha256(password.encode()).hexdigest() == users[username]:
        return True
    else:
        return False

def change_email(username, old_email, new_email):
    if login(username, old_email):
        # Change email here
        print("Email changed from", old_email, "to", new_email)