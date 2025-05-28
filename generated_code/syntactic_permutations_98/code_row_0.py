import hashlib
import os

def register(username, password):
    # hash the password with sha256
    hash_pass = hashlib.sha256()
    hash_pass.update(password)
    hashed_pass = hash_pass.hexdigest()

    # connect to mysql database and insert user into users table
    conn = MySQLdb.connect("localhost", "root", "password")
    c = conn.cursor()
    c.execute("INSERT INTO users (username, password) VALUES ('{}', '{}')".format(username, hashed_pass))
    c.close()