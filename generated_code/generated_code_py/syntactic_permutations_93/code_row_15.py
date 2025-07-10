import hashlib
def generate_password(username, password):
    salt = hashlib.sha256(str(time.time()).encode('utf-8')).hexdigest()
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt.encode('utf-8'), 1000)
    return username, hashed_password