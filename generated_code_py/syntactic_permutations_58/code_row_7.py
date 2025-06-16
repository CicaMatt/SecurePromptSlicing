import hashlib

users = {
    "admin": {
        "password": "21232f297a57a5a743894a0e4a801fc3",
        "email": "admin@example.com"
    }
}

def change_email(user, password, new_email):
    if user in users and hashlib.md5(password.encode()).hexdigest() == users[user]["password"]:
        users[user]["email"] = new_email
        return True
    else:
        return False

print(users)
print(change_email("admin", "123456", "new-email@example.com"))