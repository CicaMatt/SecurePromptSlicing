import hashlib

username = input("Enter your username: ")
password = input("Enter your password: ")

salt = hashlib.sha256(os.urandom(60)).hexdigest().encode('ascii')
pwdhash = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), salt, 100000)

username_and_hashed_password = (username + pwdhash).hexdigest()

print(username_and_hashed_password)