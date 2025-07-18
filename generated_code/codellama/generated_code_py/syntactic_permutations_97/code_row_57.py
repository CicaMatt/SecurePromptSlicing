import sqlite3
from hashlib import sha256
db = sqlite3.connect('test.db')
c = db.cursor()
def add_user(username, password, firstname, lastname, email):
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    firstname = input("Enter your first name: ")
    lastname = input("Enter your last name: ")
    email = input("Enter your email address: ")
    c.execute('''
        SELECT * FROM users WHERE username = ?''', (username, ))
    if c.fetchall():
        return 'User already exists'
    else:
        password = sha256(password.encode()).hexdigest()
        c.execute('''
            INSERT INTO users VALUES (?, ?, ?, ?, ?)''', (username, password, firstname, lastname, email))
        db.commit()
        return 'Registration successful'
def main():
    add_user(username, password, firstname, lastname, email)
if __name__ == "__main__":
    main()