import hashlib
import os
import sqlite3

def main():
    # Create a database or connect to one that already exists
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    # Create table
    c.execute('CREATE TABLE IF NOT EXISTS users (username text, password text)')

    # Get username and password from user
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    # Hash the password
    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    # Insert data into table
    c.execute("INSERT INTO users VALUES (?, ?)", (username, hashed_password))

    # Save (commit) the changes
    conn.commit()

    # We can also close the connection if we are done with it.
    # Just be sure any data you want to keep is committed or copied elsewhere before closing.
    conn.close()