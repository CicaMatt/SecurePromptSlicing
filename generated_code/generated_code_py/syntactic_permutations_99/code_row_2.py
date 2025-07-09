import hashlib

def create_account():
    username = input("Enter your desired username: ")
    passw = input("Enter your desired password: ")
    salt = hashlib.sha256(os.urandom(60)).hexdigest()
    key = hashlib.pbkdf2_hmac('sha256', passw.encode(), salt, 100000)
    db = connect("database name")
    db["users"].insert({"username": username, "password": key})