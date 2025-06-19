import hashlib
import sqlite3

username = input("Enter your desired username: ")
password = input("Enter your desired password: ")

hash_object = hashlib.sha256(b'random salt')
hex_dig = hash_object.hexdigest()

db = sqlite3.connect('registrationDB.db')
cursor = db.cursor()

create_table = """CREATE TABLE IF NOT EXISTS user (
    id INTEGER PRIMARY KEY,
    username TEXT NOT NULL,
    password TEXT NOT NULL
);"""

cursor.execute(create_table)

insert_data = "INSERT INTO user VALUES (NULL, ?, ?)"
cursor.execute(insert_data, (username, hex_dig))

db.commit()
print("Registration Successful!")