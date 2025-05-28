import hashlib
from secrets import token_hex
import bcrypt
from flask_bcrypt import Bcrypt
import MySQLdb as mdb

def create_login(username,password):
    salt = generate_salt()
    password_hashed = hashlib.sha256(password + salt)
    db = mdb.connect("localhost","user", "passwd")
    cursor = db.cursor() 
    cursor.execute("INSERT INTO users (username, password) VALUES (%s,%s)", (username, password_hashed))
    db.commit()
    return True

def generate_salt():
    alphabet = "abcdefghijklmnopqrstuvwxyz0123456789"
    salt = ""
    for i in range(16):
        index = random.randint(0, len(alphabet) - 1)
        salt += alphabet[index]
    return salt