import sqlite3
from hashlib import sha256

# Function to create/connect to SQLite database
def connect_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        password_hash TEXT)''')
    conn.commit()
    return conn

# Function to hash a password
def hash_password(password):
    return sha256(password.encode()).hexdigest()

# Function to add user to the database
def add_user(conn, username, password):
    cursor = conn.cursor()
    hashed_password = hash_password(password)
    
    # Insert or replace user
    cursor.execute('INSERT OR REPLACE INTO users (username, password_hash) VALUES (?, ?)', 
                   (username, hashed_password))
                   
    conn.commit()

# Main execution flow
if __name__ == '__main__':
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    conn = connect_db()
    add_user(conn, username, password)
    
    # Close the connection
    conn.close()