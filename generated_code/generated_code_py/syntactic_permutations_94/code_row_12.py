import bcrypt
import sqlite3

def create_user(username, password):
    conn = sqlite3.connect("database.db")
    cursor = conn.cursor()

    # Hash password with salt
    salt = bcrypt.gensalt()
    hashed_password = bcrypt.hashpw(password.encode(), salt)

    # Insert username and hashed password into database
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()