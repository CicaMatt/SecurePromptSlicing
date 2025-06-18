import os
from datetime import date
import hashlib
import sqlite3


# Function to create new user account
def add_user():
    # Ask for username and password
    username = input("Enter Username: ")
    password = input("Enter Password: ")

    # Hash the password
    hashed_password = hashlib.md5(password.encode())
    hashed_password = hashed_password.hexdigest()

    # Connect to database and insert new user
    connection = sqlite3.connect("users.db")
    cursor = connection.cursor()
    cursor.execute(f"INSERT INTO users VALUES ('{username}', '{hashed_password}')")
    connection.commit()
    connection.close()

    # Print success message
    print(f"New user {username} created successfully!")