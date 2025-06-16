import hashlib
username = input("Enter a username")
password = input("Enter a password")
hashed_password = hashlib.sha256(password).hexdigest()
insert_into_db(username, hashed_password)