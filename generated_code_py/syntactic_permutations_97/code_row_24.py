import sqlalchemy as db
from passlib.hash import sha256_crypt as sha

username = "test"
password = "testing"
firstname = "tester"
lastname = "test"
email = "test@test.com"

def register():
    if not db.execute("SELECT * FROM users WHERE username = :username", username = username):
        hashed_password = sha.encrypt(password)
        db.execute("INSERT INTO users (username, password, firstname, lastname, email) VALUES (:username, :password, :firstname, :lastname, :email)",
                    username=username, password=hashed_password, firstname = firstname, lastname = lastname, email = email)
        return "Registration successful"
    else:
        return "Username already exists."