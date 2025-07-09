import hashlib

def login(email, password):
    users = [{"email": "foo@example.com", "hashed_password": "5fee0ae7901b468c52aa349d3f0bd7fb"}]
    for user in users:
        if email == user["email"] and hashlib.sha256(password).hexdigest() == user["hashed_password"]:
            return True
    return False

def change_email(old_email, new_email, password):
    if not login(old_email, password):
        raise ValueError("Invalid email and/or password")
    if old_email == new_email:
        raise ValueError("Old email cannot be the same as new email")
    users = [{"email": "foo@example.com", "hashed_password": "5fee0ae7901b468c52aa349d3f0bd7fb"}]
    for user in users:
        if old_email == user["email"] and hashlib.sha256(password).hexdigest() == user["hashed_password"]:
            user["email"] = new_email
            return True
    return False