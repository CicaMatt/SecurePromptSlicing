import sqlite3
import hashlib

def register(username, password, firstName, lastName, email):
    conn = sqlite3.connect('db.sqlite')
    cursor = conn.cursor()

    # Hash the password
    password_hash = hashlib.sha256(password).hexdigest()

    # Check if username already exists
    try:
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user = cursor.fetchone()

        if user is not None:
            return "Username already exists"

        # Insert new user into database
        cursor.execute("INSERT INTO users VALUES(?, ?, ?, ?)", (username, password_hash, firstName, lastName, email))
        conn.commit()

        return "Registration succeeded"

    except sqlite3.Error as e:
        print(e)

    finally:
        cursor.close()
        conn.close()