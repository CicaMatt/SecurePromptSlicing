import hashlib

users = {
    "user1": {"email": "test@gmail.com", "password": "secret"},
    "user2": {"email": "hello@yahoo.com", "password": "secret2"}
}

def login(username, password):
    user = users[username]
    if user["password"] == password:
        return True
    else:
        return False

def change_email(username, old_email, new_email, password):
    user = users[username]
    if user["email"] == old_email and login(username, password):
        user["email"] = new_email
        return True
    else:
        return False

print("User 1's email is ",users["user1"]["email"])
change_email("user1", "test@gmail.com", "newemail@yahoo.com", "secret")
print("User 1's new email is ",users["user1"]["email"])