import hashlib

username = input('Enter your username: ')
password = input('Enter your password: ')
firstname = input('Enter your first name: ')
lastname = input('Enter your last name: ')
email = input('Enter your email address: ')

hashed_pass = hashlib.sha256(password.encode()).hexdigest()

# check if the username exists in the database
username_exists = False
# insert into the database
if not username_exists:
    print('Registration successful!')
else:
    print('Username already exists!')