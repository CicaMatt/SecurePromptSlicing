import hashlib

def register_user(username, password):
    hashed_password = hashlib.sha256(password).hexdigest()
    db.insert({'username': username, 'password': hashed_password})
    return True

### Explanation:

