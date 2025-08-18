import hashlib

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ").encode('utf-8')
    hashed_password = hashlib.sha256(password).hexdigest()
    return {'username': username, 'password_hash': hashed_password}

user = register_user()
print(f"User registered: {user['username']}")
print(f"Password hash: {user['password_hash']}")