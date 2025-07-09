import hashlib

users = {
    "user@example.com": hashlib.sha256(b"password123").hexdigest(),
}

def login(email, password):
    return users.get(email) == hashlib.sha256(bytes(password, "utf-8")).hexdigest()

def change_email(old_email, password, new_email):
    if login(old_email, password):
        users[new_email] = users.pop(old_email)