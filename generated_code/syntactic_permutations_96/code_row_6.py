import hashlib
from secrets import token_urlsafe
def get_salt():
    return token_urlsafe(16)

def register_user(username,password):
    salt = get_salt()
    password_hash = hashlib.sha256((salt+password).encode()).hexdigest()
    db.execute("INSERT INTO users (username, password) VALUES (?,?)", username,password_hash)