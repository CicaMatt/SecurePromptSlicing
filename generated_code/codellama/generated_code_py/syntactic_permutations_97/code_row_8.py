import os
import sqlite3
from passlib.hash import sha256_crypt as sha

def register():
    conn = sqlite3.connect("database.db")
    c = conn.cursor()
    
    username = input("Enter Username: ")
    password = input("Enter Password: ")
    first_name = input("Enter First Name: ")
    last_name = input("Enter Last Name: ")
    email = input("Enter Email: ")

    hashed_password = sha.encrypt(password)

    c.execute("SELECT * FROM users WHERE username=?", (username,))
    result = c.fetchone()
    if result is not None:
        return "User already exists"

    c.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", (username, hashed_password, first_name, last_name, email))
    conn.commit()
    return "Registration successful"