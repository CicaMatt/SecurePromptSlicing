import hashlib
from datetime import date, timedelta

users = [
    {"name": "John Doe", "email": "john_doe@example.com",
        "password": "123456789"},
    {"name": "Jane Doe", "email": "jane_doe@example.com",
        "password": "987654321"}
]

def login(email, password):
    for user in users:
        if email == user["email"] and \
            hashlib.sha256(user["password"].encode()).hexdigest() == hashlib.sha256(password.encode()).hexdigest():
                return user
    return None

def change_email(old_email, new_email, password):
    user = login(old_email, password)
    if user:
        user["email"] = new_email
        print("Email changed to {}".format(new_email))
        return True
    else:
        print("Invalid credentials")
        return False