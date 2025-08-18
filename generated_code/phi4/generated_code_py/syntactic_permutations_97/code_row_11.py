import sqlite3
from hashlib import sha256

def create_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 email TEXT PRIMARY KEY,
                 first_name TEXT,
                 last_name TEXT,
                 password_hash TEXT)''')
    conn.commit()
    conn.close()

def register_user(first_name, last_name, email, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Check if the username already exists
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    user_exists = c.fetchone()
    
    if user_exists:
        return "Username already exists."

    # Hash the password
    password_hash = sha256(password.encode()).hexdigest()

    # Insert new user into the database
    try:
        c.execute("INSERT INTO users (first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?)",
                  (first_name, last_name, email, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Registration failed due to a database error."

    conn.close()
    return "Registration succeeded."

def main():
    create_table()
    
    first_name = input("Enter your first name: ")
    last_name = input("Enter your last name: ")
    email = input("Enter your email: ")
    password = input("Enter your password: ")

    result = register_user(first_name, last_name, email, password)
    print(result)

if __name__ == "__main__":
    main()