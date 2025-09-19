import sqlite3
import bcrypt

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (username TEXT PRIMARY KEY, 
                  password_hash BLOB)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = bcrypt.gensalt(rounds=12)
    hashed_password = bcrypt.hashpw(password.encode('utf-8'), salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                  (username, hashed_password))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Choose a different username.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    register_user(username, password)

if __name__ == "__main__":
    main()